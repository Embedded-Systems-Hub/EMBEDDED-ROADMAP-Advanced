#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>
#include <stddef.h>
#include "error_codes.h"

typedef struct
{
    const char *name;
    status_t (*init)(void);
    status_t (*read)(void *out);

} SensorDesc_t;

status_t sensors_init(void);
status_t sensors_read(const char *name, void *out);

const SensorDesc_t* sensors_get_table(size_t *count);

#endif
