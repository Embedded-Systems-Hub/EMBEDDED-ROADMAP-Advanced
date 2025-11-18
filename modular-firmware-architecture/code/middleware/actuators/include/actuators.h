#ifndef ACTUATORS_H
#define ACTUATORS_H

#include <stddef.h>

typedef struct
{
    const char *name;
    void (*init)(void);
    void (*write)(const void *data);

} ActuatorDesc_t;

void actuators_init(void);
void actuators_write(const char *name, const void *data);

const ActuatorDesc_t* actuators_get_table(size_t *count);

#endif
