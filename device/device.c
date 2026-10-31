#include "device.h"
#include <limits.h>

int get_temperature(void) {
    return 25;
}

/*
-1 - error
0 - no values written
1 or higher - num of values written
*/
int device_read_temperatures(int *buffer, size_t capacity){
    if (buffer == NULL || capacity > (size_t)INT_MAX) {
        return -1; // error: null pointer or invalid capacity
    }

    if (capacity == 0) {
        return 0; // no values written
    }

    for (size_t i = 0; i < capacity; ++i) {
        buffer[i] = 25 + (int)(i % 5); // Example: fill with dummy temperature values
    }

    return (int)capacity; // return the number of values written
}