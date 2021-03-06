#include "can.h"

static CanardInstance canard;
static uavcan_protocol_NodeStatus node_status;
static uint8_t inout_transfer_id = 0;

// Max size of sonar transfer is ~4K, not sure how much memory overhead they have
// libcanard memory pool for storing TX queue.
#define CANARD_MEM_POOL_SIZE    5000
static uint8_t canard_mem_pool[CANARD_MEM_POOL_SIZE];
static uint8_t canard_message_buffer[ARVP_SONAR_RAWDATA_MAX_SIZE];

static CanardSTM32CANTimings canard_timings;

static void can_gpio_init() {
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef gpio;

    // TODO match these to hardware
    gpio.Pin = GPIO_PIN_12 | GPIO_PIN_13;
    gpio.Alternate = GPIO_AF7_CAN;
    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_MEDIUM;

    HAL_GPIO_Init(GPIOA, &gpio);
}

static void on_reception(CanardInstance* ins,
                         CanardRxTransfer* transfer);

static bool should_accept(const CanardInstance* ins,
                          uint64_t* out_data_type_signature,
                          uint16_t data_type_id,
                          CanardTransferType transfer_type,
                          uint8_t source_node_id);

void can_init(void) {
    __HAL_RCC_CAN1_CLK_ENABLE();

    can_gpio_init();

    // Compute timings and initialize CAN peripheral
    canardSTM32ComputeCANTimings(72000000, 1000000, &canard_timings);
    canardSTM32Init(&canard_timings, CanardSTM32IfaceModeNormal);
    
    // Initialise libcanard instance, and set node ID
    canardInit(&canard,
        (void*) &canard_mem_pool,
        CANARD_MEM_POOL_SIZE,
        on_reception,
        should_accept,
        NULL);
    canardSetLocalNodeID(&canard, UAVCAN_NODE_ID);
    
    // Set initial node status
    node_status.health = UAVCAN_PROTOCOL_NODESTATUS_HEALTH_OK;
    node_status.mode = UAVCAN_PROTOCOL_NODESTATUS_MODE_INITIALIZATION;
    node_status.vendor_specific_status_code = UAVCAN_VS_ERROR_OK;

    // Set up interrupts for TX
}

void USB_HP_CAN_TX_IRQHandler(void) {
    // TODO handle transmit error somehow

    // If any of the sending is finished
    if (CAN->TSR & (CAN_TSR_RQCP0 | CAN_TSR_RQCP1 | CAN_TSR_RQCP2)) {
        // Send next message
        const CanardCANFrame* out_frame = canardPeekTxQueue(&canard);
        if (out_frame != NULL) {
            // Transmit and clear TX queue
            canardSTM32Transmit(out_frame);
            canardPopTxQueue(&canard);
        } else {
            check_sending_status();
        }

        // Clear bits
        if (CAN->TSR & CAN_TSR_RQCP0) {
            SET_BIT(CAN->TSR, CAN_TSR_RQCP0);
        } else if (CAN->TSR & CAN_TSR_RQCP1) {
            SET_BIT(CAN->TSR, CAN_TSR_RQCP1);
        } else if (CAN->TSR & CAN_TSR_RQCP2) {
            SET_BIT(CAN->TSR, CAN_TSR_RQCP2);
        }
    }
}

static void can_panic(uint8_t vs_error);

void can_send_raw_data(sonar_channel_t channel,
                        uint16_t* p_data, uint16_t num_samples) {

    arvp_sonar_RawData in_data;
    in_data.hydrophone_id = channel;
    // TODO get gain as well
    in_data.data.len = num_samples;
    in_data.data.data = p_data;

    // Encode message
    uint32_t msg_len = arvp_sonar_RawData_encode(&in_data, canard_message_buffer);


    int16_t err = canardBroadcast(&canard,
        ARVP_SONAR_RAWDATA_SIGNATURE,
        UAVCAN_SONAR_RAWDATA_DATATYPE_ID,
        &inout_transfer_id,
        0,  // These messages are very low priority.
        (void*) canard_message_buffer,
        msg_len);

    // Want to be able to relatively easily catch if we run out of memory
    if (err == -3) {
        can_panic(UAVCAN_VS_ERROR_NO_MEM);
    }
}

static void can_panic(uint8_t vs_error) {
    // Publish error node status urgently
    node_status.health = UAVCAN_PROTOCOL_NODESTATUS_HEALTH_WARNING;
    node_status.mode = UAVCAN_PROTOCOL_NODESTATUS_MODE_OFFLINE;
    node_status.vendor_specific_status_code = vs_error;

    // Pop all frames off queue
    while (canardPeekTxQueue(&canard) != NULL) {
        canardPopTxQueue(&canard);
    }

    // Encode message
    uint32_t msg_len = uavcan_protocol_NodeStatus_encode(&node_status, canard_message_buffer);

    canardBroadcast(&canard,
        UAVCAN_PROTOCOL_NODESTATUS_SIGNATURE,
        UAVCAN_PROTOCOL_NODESTATUS_ID,
        &inout_transfer_id,
        CANARD_TRANSFER_PRIORITY_HIGHEST,
        &canard_message_buffer,
        msg_len);

    const CanardCANFrame* p_frame = canardPeekTxQueue(&canard);
    canardSTM32Transmit(p_frame);
    
    while(1);
}


static void can_publish_node_status() {
    uint32_t msg_len = uavcan_protocol_NodeStatus_encode(&node_status, canard_message_buffer);

    canardBroadcast(&canard,
        UAVCAN_PROTOCOL_NODESTATUS_SIGNATURE,
        UAVCAN_PROTOCOL_NODESTATUS_ID,
        &inout_transfer_id,
        CANARD_TRANSFER_PRIORITY_HIGHEST,
        &canard_message_buffer,
        msg_len);

}

void can_periodic(uint64_t current_time_usec) {
    canardCleanupStaleTransfers(&canard, current_time_usec);
    can_publish_node_status();
}

void can_start_transmit(void) {
    // Send message
    const CanardCANFrame* out_frame = canardPeekTxQueue(&canard);
    if (out_frame != NULL) {
        // Transmit and clear TX queue
        canardSTM32Transmit(out_frame);
        canardPopTxQueue(&canard);
    }
}


// TODO finish CAN
static void on_reception(CanardInstance* ins,
                         CanardRxTransfer* transfer) {

    // Not receiving anything yet
    if (transfer->transfer_type == CanardTransferTypeRequest) {
        switch (transfer->data_type_id) {
            case (UAVCAN_PROTOCOL_PARAM_GETSET_ID):
                //comms_get_set_id(ins, transfer);
                break;
            case (UAVCAN_PROTOCOL_RESTARTNODE_ID):
                //comms_restart_node(ins, transfer);
                break;
            case (UAVCAN_PROTOCOL_GETNODEINFO_ID):
                //comms_get_node_info(ins, transfer);
                break;
        }
    }
}

static bool should_accept(const CanardInstance* ins,
                          uint64_t* out_data_type_signature,
                          uint16_t data_type_id,
                          CanardTransferType transfer_type,
                          uint8_t source_node_id) {
    // Not receiving anything yet
    if (transfer_type == CanardTransferTypeRequest) {
        switch (data_type_id) {
            case (UAVCAN_PROTOCOL_PARAM_GETSET_ID):
                *out_data_type_signature = UAVCAN_PROTOCOL_PARAM_GETSET_SIGNATURE;
                return true;
            case (UAVCAN_PROTOCOL_RESTARTNODE_ID):
                return true;
            case (UAVCAN_PROTOCOL_GETNODEINFO_ID):
                return true;
            default:
                return false;
        }
    }
    return false;
}