/*
 * UAVCAN data structure definition for libcanard.
 *
 * Autogenerated, do not edit.
 *
 * Source file: /home/isthatme/Documents/Clubs/ARVP/sonar_firmware/dsdl/uavcan/equipment/air_data/1027.RawAirData.uavcan
 */

#ifndef __UAVCAN_EQUIPMENT_AIR_DATA_RAWAIRDATA
#define __UAVCAN_EQUIPMENT_AIR_DATA_RAWAIRDATA

#include <stdint.h>
#include "canard.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************* Source text **********************************
#
# Raw Air Data.
#

# Note: unused vars should be assigned NaN

#
# Heater State
#
uint8 FLAG_HEATER_AVAILABLE      = 1
uint8 FLAG_HEATER_WORKING        = 2
uint8 FLAG_HEATER_OVERCURRENT    = 4
uint8 FLAG_HEATER_OPENCIRCUIT    = 8
uint8 flags

#
# Pressure Data
#
float32 static_pressure                 # Pascal
float32 differential_pressure           # Pascal

#
# Temperature Data
#
float16 static_pressure_sensor_temperature          # Kelvin
float16 differential_pressure_sensor_temperature    # Kelvin

float16 static_air_temperature          # Kelvin
                                        # This field contains the raw temperature reading
                                        # from the externally mounted temperature sensor or,
                                        # in absence of one, the raw temperature of the pressure sensor.

float16 pitot_temperature               # Kelvin

float16[<=16] covariance                # order of diagonal elements :
                                        # static_pressure, differential_pressure,
                                        # static_air_temperature, pitot_temperature
                                        # Pascal^2 for pressure variance and covariance
                                        # Kevin^2 for Temperature variance and covariance
                                        # Pascal*Kelvin for pressure/temperature covariance
******************************************************************************/

/********************* DSDL signature source definition ***********************
uavcan.equipment.air_data.RawAirData
saturated uint8 flags
saturated float32 static_pressure
saturated float32 differential_pressure
saturated float16 static_pressure_sensor_temperature
saturated float16 differential_pressure_sensor_temperature
saturated float16 static_air_temperature
saturated float16 pitot_temperature
saturated float16[<=16] covariance
******************************************************************************/

#define UAVCAN_EQUIPMENT_AIR_DATA_RAWAIRDATA_ID            1027
#define UAVCAN_EQUIPMENT_AIR_DATA_RAWAIRDATA_NAME          "uavcan.equipment.air_data.RawAirData"
#define UAVCAN_EQUIPMENT_AIR_DATA_RAWAIRDATA_SIGNATURE     (0xC77DF38BA122F5DAULL)

#define UAVCAN_EQUIPMENT_AIR_DATA_RAWAIRDATA_MAX_SIZE      ((397 + 7)/8)

// Constants
#define UAVCAN_EQUIPMENT_AIR_DATA_RAWAIRDATA_FLAG_HEATER_AVAILABLE            1 // 1
#define UAVCAN_EQUIPMENT_AIR_DATA_RAWAIRDATA_FLAG_HEATER_WORKING              2 // 2
#define UAVCAN_EQUIPMENT_AIR_DATA_RAWAIRDATA_FLAG_HEATER_OVERCURRENT          4 // 4
#define UAVCAN_EQUIPMENT_AIR_DATA_RAWAIRDATA_FLAG_HEATER_OPENCIRCUIT          8 // 8

#define UAVCAN_EQUIPMENT_AIR_DATA_RAWAIRDATA_COVARIANCE_MAX_LENGTH                       16

typedef struct
{
    // FieldTypes
    uint8_t    flags;                         // bit len 8
    float      static_pressure;               // float32 Saturate
    float      differential_pressure;         // float32 Saturate
    float      static_pressure_sensor_temperature; // float16 Saturate
    float      differential_pressure_sensor_temperature; // float16 Saturate
    float      static_air_temperature;        // float16 Saturate
    float      pitot_temperature;             // float16 Saturate
    struct
    {
        uint8_t    len;                       // Dynamic array length
        float*     data;                      // Dynamic Array 16bit[16] max items
    } covariance;

} uavcan_equipment_air_data_RawAirData;

extern
uint32_t uavcan_equipment_air_data_RawAirData_encode(uavcan_equipment_air_data_RawAirData* source, void* msg_buf);

extern
int32_t uavcan_equipment_air_data_RawAirData_decode(const CanardRxTransfer* transfer, uint16_t payload_len, uavcan_equipment_air_data_RawAirData* dest, uint8_t** dyn_arr_buf);

extern
uint32_t uavcan_equipment_air_data_RawAirData_encode_internal(uavcan_equipment_air_data_RawAirData* source, void* msg_buf, uint32_t offset, uint8_t root_item);

extern
int32_t uavcan_equipment_air_data_RawAirData_decode_internal(const CanardRxTransfer* transfer, uint16_t payload_len, uavcan_equipment_air_data_RawAirData* dest, uint8_t** dyn_arr_buf, int32_t offset);

#ifdef __cplusplus
} // extern "C"
#endif
#endif // __UAVCAN_EQUIPMENT_AIR_DATA_RAWAIRDATA