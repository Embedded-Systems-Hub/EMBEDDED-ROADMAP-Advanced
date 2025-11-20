#ifndef SENSORS_H
#define SENSORS_H

#include <stddef.h>

typedef struct
{
    const char *name;
    void (*init)(void);
    float (*read)(void);

} SensorDesc_t;

void sensors_init(void);
float sensors_read(const char *name);

const SensorDesc_t* sensors_get_table(size_t *count);

#endif
