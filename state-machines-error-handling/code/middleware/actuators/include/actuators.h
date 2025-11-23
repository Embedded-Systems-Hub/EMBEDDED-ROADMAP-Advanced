#ifndef ACTUATORS_H
#define ACTUATORS_H

#include <stddef.h>
#include "error_codes.h"

/*
 * Generic actuator descriptor that abstracts actuator initialization
 * and write operations through function pointers.
 * The middleware uses this table to discover and interact with actuators.
 */
typedef struct
{
    const char *name;                 /* Logical actuator name */
    status_t (*init)(void);           /* Initialization callback */
    status_t (*write)(const void *data); /* Write/update callback */
} ActuatorDesc_t;

/* Initialize all registered actuators. */
status_t actuators_init(void);

/* Write/update an actuator by its registered name. */
status_t actuators_write(const char *name, const void *data);

/* Returns the static actuator descriptor table. */
const ActuatorDesc_t* actuators_get_table(size_t *count);

#endif /* ACTUATORS_H */
