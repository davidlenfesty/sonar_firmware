/*
 * UAVCAN data structure definition for libcanard.
 *
 * Autogenerated, do not edit.
 *
 * Source file: /home/isthatme/Documents/Clubs/ARVP/sonar_firmware/dsdl/uavcan/equipment/camera_gimbal/1044.Status.uavcan
 */

#ifndef __UAVCAN_EQUIPMENT_CAMERA_GIMBAL_STATUS
#define __UAVCAN_EQUIPMENT_CAMERA_GIMBAL_STATUS

#include <stdint.h>
#include "canard.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include <uavcan/equipment/camera_gimbal/Mode.h>

/******************************* Source text **********************************
#
# Generic gimbal status.
#

uint8 gimbal_id

Mode mode

#
# Camera axis orientation in body frame (not in fixed frame).
# Please refer to the UAVCAN coordinate frame conventions.
#
float16[4] camera_orientation_in_body_frame_xyzw
float16[<=9] camera_orientation_in_body_frame_covariance   # +inf for non-existent axes
******************************************************************************/

/********************* DSDL signature source definition ***********************
uavcan.equipment.camera_gimbal.Status
saturated uint8 gimbal_id
uavcan.equipment.camera_gimbal.Mode mode
saturated float16[4] camera_orientation_in_body_frame_xyzw
saturated float16[<=9] camera_orientation_in_body_frame_covariance
******************************************************************************/

#define UAVCAN_EQUIPMENT_CAMERA_GIMBAL_STATUS_ID           1044
#define UAVCAN_EQUIPMENT_CAMERA_GIMBAL_STATUS_NAME         "uavcan.equipment.camera_gimbal.Status"
#define UAVCAN_EQUIPMENT_CAMERA_GIMBAL_STATUS_SIGNATURE    (0xB9F127865BE0D61EULL)

#define UAVCAN_EQUIPMENT_CAMERA_GIMBAL_STATUS_MAX_SIZE     ((228 + 7)/8)

// Constants

#define UAVCAN_EQUIPMENT_CAMERA_GIMBAL_STATUS_CAMERA_ORIENTATION_IN_BODY_FRAME_XYZW_LENGTH 4
#define UAVCAN_EQUIPMENT_CAMERA_GIMBAL_STATUS_CAMERA_ORIENTATION_IN_BODY_FRAME_COVARIANCE_MAX_LENGTH 9

typedef struct
{
    // FieldTypes
    uint8_t    gimbal_id;                     // bit len 8
    uavcan_equipment_camera_gimbal_Mode mode;                          //
    float      camera_orientation_in_body_frame_xyzw[4]; // Static Array 16bit[4] max items
    struct
    {
        uint8_t    len;                       // Dynamic array length
        float*     data;                      // Dynamic Array 16bit[9] max items
    } camera_orientation_in_body_frame_covariance;

} uavcan_equipment_camera_gimbal_Status;

extern
uint32_t uavcan_equipment_camera_gimbal_Status_encode(uavcan_equipment_camera_gimbal_Status* source, void* msg_buf);

extern
int32_t uavcan_equipment_camera_gimbal_Status_decode(const CanardRxTransfer* transfer, uint16_t payload_len, uavcan_equipment_camera_gimbal_Status* dest, uint8_t** dyn_arr_buf);

extern
uint32_t uavcan_equipment_camera_gimbal_Status_encode_internal(uavcan_equipment_camera_gimbal_Status* source, void* msg_buf, uint32_t offset, uint8_t root_item);

extern
int32_t uavcan_equipment_camera_gimbal_Status_decode_internal(const CanardRxTransfer* transfer, uint16_t payload_len, uavcan_equipment_camera_gimbal_Status* dest, uint8_t** dyn_arr_buf, int32_t offset);

#ifdef __cplusplus
} // extern "C"
#endif
#endif // __UAVCAN_EQUIPMENT_CAMERA_GIMBAL_STATUS