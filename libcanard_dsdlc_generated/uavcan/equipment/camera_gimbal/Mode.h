/*
 * UAVCAN data structure definition for libcanard.
 *
 * Autogenerated, do not edit.
 *
 * Source file: /home/isthatme/Documents/Clubs/ARVP/sonar_firmware/dsdl/uavcan/equipment/camera_gimbal/Mode.uavcan
 */

#ifndef __UAVCAN_EQUIPMENT_CAMERA_GIMBAL_MODE
#define __UAVCAN_EQUIPMENT_CAMERA_GIMBAL_MODE

#include <stdint.h>
#include "canard.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************* Source text **********************************
#
# Gimbal operating mode
#

uint8 COMMAND_MODE_ANGULAR_VELOCITY        = 0
uint8 COMMAND_MODE_ORIENTATION_FIXED_FRAME = 1
uint8 COMMAND_MODE_ORIENTATION_BODY_FRAME  = 2
uint8 COMMAND_MODE_GEO_POI                 = 3
uint8 command_mode
******************************************************************************/

/********************* DSDL signature source definition ***********************
uavcan.equipment.camera_gimbal.Mode
saturated uint8 command_mode
******************************************************************************/

#define UAVCAN_EQUIPMENT_CAMERA_GIMBAL_MODE_NAME           "uavcan.equipment.camera_gimbal.Mode"
#define UAVCAN_EQUIPMENT_CAMERA_GIMBAL_MODE_SIGNATURE      (0x9108C7785AEB69C4ULL)

#define UAVCAN_EQUIPMENT_CAMERA_GIMBAL_MODE_MAX_SIZE       ((8 + 7)/8)

// Constants
#define UAVCAN_EQUIPMENT_CAMERA_GIMBAL_MODE_COMMAND_MODE_ANGULAR_VELOCITY          0 // 0
#define UAVCAN_EQUIPMENT_CAMERA_GIMBAL_MODE_COMMAND_MODE_ORIENTATION_FIXED_FRAME          1 // 1
#define UAVCAN_EQUIPMENT_CAMERA_GIMBAL_MODE_COMMAND_MODE_ORIENTATION_BODY_FRAME          2 // 2
#define UAVCAN_EQUIPMENT_CAMERA_GIMBAL_MODE_COMMAND_MODE_GEO_POI              3 // 3

typedef struct
{
    // FieldTypes
    uint8_t    command_mode;                  // bit len 8

} uavcan_equipment_camera_gimbal_Mode;

extern
uint32_t uavcan_equipment_camera_gimbal_Mode_encode(uavcan_equipment_camera_gimbal_Mode* source, void* msg_buf);

extern
int32_t uavcan_equipment_camera_gimbal_Mode_decode(const CanardRxTransfer* transfer, uint16_t payload_len, uavcan_equipment_camera_gimbal_Mode* dest, uint8_t** dyn_arr_buf);

extern
uint32_t uavcan_equipment_camera_gimbal_Mode_encode_internal(uavcan_equipment_camera_gimbal_Mode* source, void* msg_buf, uint32_t offset, uint8_t root_item);

extern
int32_t uavcan_equipment_camera_gimbal_Mode_decode_internal(const CanardRxTransfer* transfer, uint16_t payload_len, uavcan_equipment_camera_gimbal_Mode* dest, uint8_t** dyn_arr_buf, int32_t offset);

#ifdef __cplusplus
} // extern "C"
#endif
#endif // __UAVCAN_EQUIPMENT_CAMERA_GIMBAL_MODE