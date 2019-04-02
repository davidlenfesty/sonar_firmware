/*
 * UAVCAN data structure definition for libcanard.
 *
 * Autogenerated, do not edit.
 *
 * Source file: /home/isthatme/Documents/Clubs/ARVP/sonar_firmware/dsdl/uavcan/equipment/ahrs/1001.MagneticFieldStrength.uavcan
 */

#ifndef __UAVCAN_EQUIPMENT_AHRS_MAGNETICFIELDSTRENGTH
#define __UAVCAN_EQUIPMENT_AHRS_MAGNETICFIELDSTRENGTH

#include <stdint.h>
#include "canard.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************* Source text **********************************
#
# Magnetic field readings, in Gauss, in body frame.
# SI units are avoided because of float16 range limitations.
# This message is deprecated. Use the newer 1002.MagneticFieldStrength2.uavcan message.
#

float16[3] magnetic_field_ga
float16[<=9] magnetic_field_covariance
******************************************************************************/

/********************* DSDL signature source definition ***********************
uavcan.equipment.ahrs.MagneticFieldStrength
saturated float16[3] magnetic_field_ga
saturated float16[<=9] magnetic_field_covariance
******************************************************************************/

#define UAVCAN_EQUIPMENT_AHRS_MAGNETICFIELDSTRENGTH_ID     1001
#define UAVCAN_EQUIPMENT_AHRS_MAGNETICFIELDSTRENGTH_NAME   "uavcan.equipment.ahrs.MagneticFieldStrength"
#define UAVCAN_EQUIPMENT_AHRS_MAGNETICFIELDSTRENGTH_SIGNATURE (0xE2A7D4A9460BC2F2ULL)

#define UAVCAN_EQUIPMENT_AHRS_MAGNETICFIELDSTRENGTH_MAX_SIZE ((196 + 7)/8)

// Constants

#define UAVCAN_EQUIPMENT_AHRS_MAGNETICFIELDSTRENGTH_MAGNETIC_FIELD_GA_LENGTH             3
#define UAVCAN_EQUIPMENT_AHRS_MAGNETICFIELDSTRENGTH_MAGNETIC_FIELD_COVARIANCE_MAX_LENGTH 9

typedef struct
{
    // FieldTypes
    float      magnetic_field_ga[3];          // Static Array 16bit[3] max items
    struct
    {
        uint8_t    len;                       // Dynamic array length
        float*     data;                      // Dynamic Array 16bit[9] max items
    } magnetic_field_covariance;

} uavcan_equipment_ahrs_MagneticFieldStrength;

extern
uint32_t uavcan_equipment_ahrs_MagneticFieldStrength_encode(uavcan_equipment_ahrs_MagneticFieldStrength* source, void* msg_buf);

extern
int32_t uavcan_equipment_ahrs_MagneticFieldStrength_decode(const CanardRxTransfer* transfer, uint16_t payload_len, uavcan_equipment_ahrs_MagneticFieldStrength* dest, uint8_t** dyn_arr_buf);

extern
uint32_t uavcan_equipment_ahrs_MagneticFieldStrength_encode_internal(uavcan_equipment_ahrs_MagneticFieldStrength* source, void* msg_buf, uint32_t offset, uint8_t root_item);

extern
int32_t uavcan_equipment_ahrs_MagneticFieldStrength_decode_internal(const CanardRxTransfer* transfer, uint16_t payload_len, uavcan_equipment_ahrs_MagneticFieldStrength* dest, uint8_t** dyn_arr_buf, int32_t offset);

#ifdef __cplusplus
} // extern "C"
#endif
#endif // __UAVCAN_EQUIPMENT_AHRS_MAGNETICFIELDSTRENGTH