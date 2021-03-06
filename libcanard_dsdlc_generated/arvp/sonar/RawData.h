/*
 * UAVCAN data structure definition for libcanard.
 *
 * Autogenerated, do not edit.
 *
 * Source file: /home/isthatme/Documents/Clubs/ARVP/sonar_firmware/custom_dsdl/arvp/sonar/RawData.uavcan
 */

#ifndef __ARVP_SONAR_RAWDATA
#define __ARVP_SONAR_RAWDATA

#include <stdint.h>
#include "canard.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************* Source text **********************************
#################
# RawData message. Used for sonar data.

# Some constants for selecting channels
uint8 CHANNEL_REF = 0
uint8 CHANNEL_A = 1
uint8 CHANNEL_B = 2
uint8 CHANNEL_C = 3

# ID so we know which hydrophone this came from
uint8 hydrophone_id

# Current gain of the channel
uint8 gain

# Raw sonar data.
# max 2048 elements because 2ms @ 1MSPS is 2000 samples
# and powers of 2 are nice.
uint16[<=2048] data
******************************************************************************/

/********************* DSDL signature source definition ***********************
arvp.sonar.RawData
saturated uint8 hydrophone_id
saturated uint8 gain
saturated uint16[<=2048] data
******************************************************************************/

#define ARVP_SONAR_RAWDATA_NAME                            "arvp.sonar.RawData"
#define ARVP_SONAR_RAWDATA_SIGNATURE                       (0xDAAAD25C027E3A37ULL)

#define ARVP_SONAR_RAWDATA_MAX_SIZE                        ((32796 + 7)/8)

// Constants
#define ARVP_SONAR_RAWDATA_CHANNEL_REF                                        0 // 0
#define ARVP_SONAR_RAWDATA_CHANNEL_A                                          1 // 1
#define ARVP_SONAR_RAWDATA_CHANNEL_B                                          2 // 2
#define ARVP_SONAR_RAWDATA_CHANNEL_C                                          3 // 3

#define ARVP_SONAR_RAWDATA_DATA_MAX_LENGTH                                               2048

typedef struct
{
    // FieldTypes
    uint8_t    hydrophone_id;                 // bit len 8
    uint8_t    gain;                          // bit len 8
    struct
    {
        uint16_t    len;                       // Dynamic array length
        uint16_t*  data;                      // Dynamic Array 16bit[2048] max items
    } data;

} arvp_sonar_RawData;

extern
uint32_t arvp_sonar_RawData_encode(arvp_sonar_RawData* source, void* msg_buf);

extern
int32_t arvp_sonar_RawData_decode(const CanardRxTransfer* transfer, uint16_t payload_len, arvp_sonar_RawData* dest, uint8_t** dyn_arr_buf);

extern
uint32_t arvp_sonar_RawData_encode_internal(arvp_sonar_RawData* source, void* msg_buf, uint32_t offset, uint8_t root_item);

extern
int32_t arvp_sonar_RawData_decode_internal(const CanardRxTransfer* transfer, uint16_t payload_len, arvp_sonar_RawData* dest, uint8_t** dyn_arr_buf, int32_t offset);

#ifdef __cplusplus
} // extern "C"
#endif
#endif // __ARVP_SONAR_RAWDATA