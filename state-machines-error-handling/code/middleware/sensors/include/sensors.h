#ifndef SENSORS_H
#define SENSORS_H

#include <stddef.h>
#include "error_codes.h"

/*
 * Generic sensor descriptor used by the middleware.
 * Each sensor provides:
 *  - a string name
 *  - an initialization callback
 *  - a read callback returning the sensor value (float)
 */
typedef struct
{
    const char *name;
    status_t (*init)(void);
    status_t (*read)(float *out_value);
} SensorDesc_t;

/* Initialize all registered sensors. */
status_t sensors_init(void);

/* Read a registered sensor by name. */
status_t sensors_read(const char *name, float *out_value);

/* Returns the static descriptor table defined in sensors_cfg. */
const SensorDesc_t* sensors_get_table(size_t *count);

#endif /* SENSORS_H */
