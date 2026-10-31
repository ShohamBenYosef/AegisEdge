#ifndef DEVICE_H
#define DEVICE_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


int get_temperature(void);

int device_read_temperatures(int *buffer, size_t capacity);



#ifdef __cplusplus
}
#endif

#endif /* DEVICE_H */