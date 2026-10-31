#include "telemetry.h"

int encode_telemetry(const struct TelemetryData *data, uint8_t* buffer, size_t capacity)
{
    if (data == NULL || buffer == NULL) {
        return -1; // invalid argument
    }

    if (capacity < TELEMETRY_ENCODED_SIZE) {
        return 0; // insufficient capacity
    }

    // one byte for version, one byte for sensor_id, two bytes for temperature, and four bytes for sequence
    buffer[0] = data->version;
    buffer[1] = data->sensor_id;

    // Encode temperature as two bytes (big-endian)
    // Since temperature is int16_t, we need to handle negative values correctly
    uint16_t temp = (uint16_t)data->temperature;
    buffer[2] = (uint8_t)((temp >> 8) & 0xFF);
    buffer[3] = (uint8_t)(temp & 0xFF);

    // Encode sequence as four bytes (big-endian)
    // Since sequence is uint32_t, we can directly encode it
    buffer[4] = (uint8_t)((data->sequence >> 24) & 0xFF);
    buffer[5] = (uint8_t)((data->sequence >> 16) & 0xFF);
    buffer[6] = (uint8_t)((data->sequence >> 8) & 0xFF);
    buffer[7] = (uint8_t)(data->sequence & 0xFF);


    return TELEMETRY_ENCODED_SIZE; // success
}

int decode_telemetry(struct TelemetryData *data, const uint8_t* buffer, size_t capacity) {
    if (data == NULL || buffer == NULL) {
        return -1; // invalid argument
    }

    if (capacity < TELEMETRY_ENCODED_SIZE) {
        return 0; // insufficient capacity
    }
    
    uint8_t version = buffer[0];

    if (version != 1) {
        return -1; // invalid version
    }
    
    uint8_t sensor_id = buffer[1];

    int16_t temperature = (int16_t)(((uint16_t)buffer[2] << 8) | (uint16_t)buffer[3]);

    if (temperature < -100 || temperature > 500) {
        return -1;
    }
    
    uint32_t seq = ((uint32_t)buffer[4] << 24) | ((uint32_t)buffer[5] << 16) | ((uint32_t)buffer[6] << 8) | (uint32_t)buffer[7];

    data->version = buffer[0]; 
    data->sensor_id = buffer[1];
    data->temperature = temperature;
    data->sequence = seq;

    return TELEMETRY_ENCODED_SIZE; // success
}