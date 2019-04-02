/*
 * UAVCAN data structure definition for libcanard.
 *
 * Autogenerated, do not edit.
 *
 * Source file: /home/isthatme/Documents/Clubs/ARVP/sonar_firmware/dsdl/uavcan/protocol/file/49.Write.uavcan
 */

#ifndef __UAVCAN_PROTOCOL_FILE_WRITE
#define __UAVCAN_PROTOCOL_FILE_WRITE

#include <stdint.h>
#include "canard.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include <uavcan/protocol/file/Error.h>
#include <uavcan/protocol/file/Path.h>

/******************************* Source text **********************************
#
# Write into a remote file.
# The server shall place the contents of the field 'data' into the file pointed by 'path' at the offset specified by
# the field 'offset'.
#
# When writing a file, the client should repeatedly call this service with data while advancing offset until the file
# is written completely. When write is complete, the client shall call the service one last time, with the offset
# set to the size of the file and with the data field empty, which will signal the server that the write operation is
# complete.
#
# When the write operation is complete, the server shall truncate the resulting file past the specified offset.
#
# Server implementation advice:
# It is recommended to implement proper handling of concurrent writes to the same file from different clients, for
# example by means of creating a staging area for uncompleted writes (like FTP servers do).
#

uint40 offset

Path path

uint8[<=192] data

---

Error error
******************************************************************************/

/********************* DSDL signature source definition ***********************
uavcan.protocol.file.Write
saturated uint40 offset
uavcan.protocol.file.Path path
saturated uint8[<=192] data
---
uavcan.protocol.file.Error error
******************************************************************************/

#define UAVCAN_PROTOCOL_FILE_WRITE_ID                      49
#define UAVCAN_PROTOCOL_FILE_WRITE_NAME                    "uavcan.protocol.file.Write"
#define UAVCAN_PROTOCOL_FILE_WRITE_SIGNATURE               (0x515AA1DC77E58429ULL)

#define UAVCAN_PROTOCOL_FILE_WRITE_REQUEST_MAX_SIZE        ((3192 + 7)/8)

// Constants

#define UAVCAN_PROTOCOL_FILE_WRITE_REQUEST_DATA_MAX_LENGTH                               192

typedef struct
{
    // FieldTypes
    uint64_t   offset;                        // bit len 40
    uavcan_protocol_file_Path path;                          //
    struct
    {
        uint8_t    len;                       // Dynamic array length
        uint8_t*   data;                      // Dynamic Array 8bit[192] max items
    } data;

} uavcan_protocol_file_WriteRequest;

extern
uint32_t uavcan_protocol_file_WriteRequest_encode(uavcan_protocol_file_WriteRequest* source, void* msg_buf);

extern
int32_t uavcan_protocol_file_WriteRequest_decode(const CanardRxTransfer* transfer, uint16_t payload_len, uavcan_protocol_file_WriteRequest* dest, uint8_t** dyn_arr_buf);

extern
uint32_t uavcan_protocol_file_WriteRequest_encode_internal(uavcan_protocol_file_WriteRequest* source, void* msg_buf, uint32_t offset, uint8_t root_item);

extern
int32_t uavcan_protocol_file_WriteRequest_decode_internal(const CanardRxTransfer* transfer, uint16_t payload_len, uavcan_protocol_file_WriteRequest* dest, uint8_t** dyn_arr_buf, int32_t offset);

#define UAVCAN_PROTOCOL_FILE_WRITE_RESPONSE_MAX_SIZE       ((16 + 7)/8)

// Constants

typedef struct
{
    // FieldTypes
    uavcan_protocol_file_Error error;                         //

} uavcan_protocol_file_WriteResponse;

extern
uint32_t uavcan_protocol_file_WriteResponse_encode(uavcan_protocol_file_WriteResponse* source, void* msg_buf);

extern
int32_t uavcan_protocol_file_WriteResponse_decode(const CanardRxTransfer* transfer, uint16_t payload_len, uavcan_protocol_file_WriteResponse* dest, uint8_t** dyn_arr_buf);

extern
uint32_t uavcan_protocol_file_WriteResponse_encode_internal(uavcan_protocol_file_WriteResponse* source, void* msg_buf, uint32_t offset, uint8_t root_item);

extern
int32_t uavcan_protocol_file_WriteResponse_decode_internal(const CanardRxTransfer* transfer, uint16_t payload_len, uavcan_protocol_file_WriteResponse* dest, uint8_t** dyn_arr_buf, int32_t offset);

#ifdef __cplusplus
} // extern "C"
#endif
#endif // __UAVCAN_PROTOCOL_FILE_WRITE