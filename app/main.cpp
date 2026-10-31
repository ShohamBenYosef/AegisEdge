#include <iostream>
#include <iomanip>

#include "device.h"
#include "telemetry.h"

void print_encoded_telemetry_data(const TelemetryData *data, uint8_t *buffer, size_t capacity) {
    int written = encode_telemetry(data, buffer, capacity);

    if (written != TELEMETRY_ENCODED_SIZE) {
        std::cout << "Encoding failed\n";
        return;
    }

    std::cout << "Encoded telemetry data: ";

    for (int i = 0; i < written; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[i]) << ' ';
    }

    std::cout << std::dec << '\n';
}

void print_decoded_telemetry_data(TelemetryData *data, const uint8_t *buffer, size_t capacity) {
    int decoded = decode_telemetry(data, buffer, capacity);

    if (decoded != TELEMETRY_ENCODED_SIZE) {
        std::cout << "Decoding failed\n";
        return;
    }

    std::cout << "Decoded Telemetry Data:\n";
    std::cout << "Version: " << static_cast<int>(data->version) << '\n';
    std::cout << "Sensor ID: " << static_cast<int>(data->sensor_id) << '\n';
    std::cout << "Temperature: " << data->temperature << '\n';
    std::cout << "Sequence: " << data->sequence << '\n';
}





int main() {
    std::cout << "Starting AegisEdges...\n";


    // valid telemetry data
    TelemetryData telemetry_data;
    telemetry_data.version = 1;
    telemetry_data.sensor_id = 7;
    telemetry_data.temperature = 25;
    telemetry_data.sequence = 0x12345678;

    uint8_t buffer[TELEMETRY_ENCODED_SIZE];

    print_encoded_telemetry_data(&telemetry_data, buffer, sizeof(buffer));

    TelemetryData decoded{};

    print_decoded_telemetry_data(&decoded, buffer, sizeof(buffer));


    // negative temperature test
    telemetry_data.temperature = -25;
    
    print_encoded_telemetry_data(&telemetry_data, buffer, sizeof(buffer));
    print_decoded_telemetry_data(&decoded, buffer,sizeof(buffer));
    

    // invalid.
    uint8_t invalid_version[TELEMETRY_ENCODED_SIZE] = {0x02, 0x07, 0x00, 0x19,0x12, 0x34, 0x56, 0x78};
    int invalid_version_result = decode_telemetry(&decoded,invalid_version,sizeof(invalid_version));

    std::cout << "Result: " << invalid_version_result << " (expected -1)\n";
    // --
    uint8_t truncated[5] = {0x01, 0x07, 0x00, 0x19, 0x12};
    int truncated_result = decode_telemetry(&decoded, truncated, sizeof(truncated));

    std::cout << "Result: " << truncated_result << " (expected 0)\n";
    // --
    uint8_t invalid_temperature[TELEMETRY_ENCODED_SIZE] = {0x01, 0x07, 0x02, 0x58,0x12, 0x34, 0x56, 0x78};
    int invalid_temperature_result = decode_telemetry(&decoded, invalid_temperature, sizeof(invalid_temperature));

    std::cout << "Result: " << invalid_temperature_result << " (expected -1)\n";
    // --
    int null_data_result = decode_telemetry(nullptr, buffer, sizeof(buffer));
    int null_buffer_result = decode_telemetry(&decoded, nullptr, sizeof(buffer));

    std::cout << "NULL data result: " << null_data_result << " (expected -1)\n";
    std::cout << "NULL buffer result: " << null_buffer_result << " (expected -1)\n";



    return 0;
}