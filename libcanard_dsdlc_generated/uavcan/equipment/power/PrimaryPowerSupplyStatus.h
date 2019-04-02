/*
 * UAVCAN data structure definition for libcanard.
 *
 * Autogenerated, do not edit.
 *
 * Source file: /home/isthatme/Documents/Clubs/ARVP/sonar_firmware/dsdl/uavcan/equipment/power/1090.PrimaryPowerSupplyStatus.uavcan
 */

#ifndef __UAVCAN_EQUIPMENT_POWER_PRIMARYPOWERSUPPLYSTATUS
#define __UAVCAN_EQUIPMENT_POWER_PRIMARYPOWERSUPPLYSTATUS

#include <stdint.h>
#include "canard.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************* Source text **********************************
#
# Primary power supply status.
# Typical publishing rate should be around 1~2 Hz.
#

#
# How many hours left to full discharge at average load over the last 10 seconds.
#
float16 hours_to_empty_at_10sec_avg_power               # [Hours]
float16 hours_to_empty_at_10sec_avg_power_variance      # [Hours^2]

#
# True if the publishing node senses that an external power source can be used, e.g. to charge batteries.
#
bool external_power_available

#
# Remaining energy estimate in percent.
#
uint7 remaining_energy_pct              # [Percent]     Required
uint7 remaining_energy_pct_stdev        # [Percent]     Error standard deviation. Use best guess if unknown.
******************************************************************************/

/********************* DSDL signature source definition ***********************
uavcan.equipment.power.PrimaryPowerSupplyStatus
saturated float16 hours_to_empty_at_10sec_avg_power
saturated float16 hours_to_empty_at_10sec_avg_power_variance
saturated bool external_power_available
saturated uint7 remaining_energy_pct
saturated uint7 remaining_energy_pct_stdev
******************************************************************************/

#define UAVCAN_EQUIPMENT_POWER_PRIMARYPOWERSUPPLYSTATUS_ID 1090
#define UAVCAN_EQUIPMENT_POWER_PRIMARYPOWERSUPPLYSTATUS_NAME "uavcan.equipment.power.PrimaryPowerSupplyStatus"
#define UAVCAN_EQUIPMENT_POWER_PRIMARYPOWERSUPPLYSTATUS_SIGNATURE (0xBBA05074AD757480ULL)

#define UAVCAN_EQUIPMENT_POWER_PRIMARYPOWERSUPPLYSTATUS_MAX_SIZE ((47 + 7)/8)

// Constants

typedef struct
{
    // FieldTypes
    float      hours_to_empty_at_10sec_avg_power; // float16 Saturate
    float      hours_to_empty_at_10sec_avg_power_variance; // float16 Saturate
    bool       external_power_available;      // bit len 1
    uint8_t    remaining_energy_pct;          // bit len 7
    uint8_t    remaining_energy_pct_stdev;    // bit len 7

} uavcan_equipment_power_PrimaryPowerSupplyStatus;

extern
uint32_t uavcan_equipment_power_PrimaryPowerSupplyStatus_encode(uavcan_equipment_power_PrimaryPowerSupplyStatus* source, void* msg_buf);

extern
int32_t uavcan_equipment_power_PrimaryPowerSupplyStatus_decode(const CanardRxTransfer* transfer, uint16_t payload_len, uavcan_equipment_power_PrimaryPowerSupplyStatus* dest, uint8_t** dyn_arr_buf);

extern
uint32_t uavcan_equipment_power_PrimaryPowerSupplyStatus_encode_internal(uavcan_equipment_power_PrimaryPowerSupplyStatus* source, void* msg_buf, uint32_t offset, uint8_t root_item);

extern
int32_t uavcan_equipment_power_PrimaryPowerSupplyStatus_decode_internal(const CanardRxTransfer* transfer, uint16_t payload_len, uavcan_equipment_power_PrimaryPowerSupplyStatus* dest, uint8_t** dyn_arr_buf, int32_t offset);

#ifdef __cplusplus
} // extern "C"
#endif
#endif // __UAVCAN_EQUIPMENT_POWER_PRIMARYPOWERSUPPLYSTATUS