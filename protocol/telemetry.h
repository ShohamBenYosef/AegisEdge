#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>



#ifdef __cplusplus
extern "C" {
#endif

enum {
    TELEMETRY_ENCODED_SIZE = 8
};

struct TelemetryData {
    uint8_t version;
    uint8_t sensor_id;
    int16_t temperature;
    uint32_t sequence;
};

/**
 * Encodes telemetry data into a buffer.
 * @param data Pointer to the telemetry data structure to be encoded.
 * @param buffer Pointer to the buffer where the encoded data will be stored.
 * @param capacity The size of the buffer.
 * @return -1 on invalid argument, 0 if insufficient capacity, 8 success.
 */
int encode_telemetry(const struct TelemetryData *data, uint8_t* buffer, size_t capacity); 

/**
 * Decodes telemetry data from a buffer.
 * @param data Pointer to the telemetry data structure where the decoded data will be stored.
 * @param buffer Pointer to the buffer containing the encoded data.
 * @param capacity The size of the buffer.
 * @return -1 on invalid argument, 0 if insufficient capacity, 8 success.
 */
int decode_telemetry(struct TelemetryData *data, const uint8_t* buffer, size_t capacity) ;

#ifdef __cplusplus
}
#endif

#endif /* TELEMETRY_H */