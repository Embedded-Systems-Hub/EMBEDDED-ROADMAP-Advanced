#ifndef ACTUATORS_H
#define ACTUATORS_H

#include <stddef.h>
#include "error_codes.h"

typedef struct
{
    const char *name;
    status_t (*init)(void);
    status_t (*write)(const void *in);

} ActuatorDesc_t;

status_t actuators_init(void);
status_t actuators_write(const char *name, const void *in);

const ActuatorDesc_t* actuators_get_table(size_t *count);

#endif
