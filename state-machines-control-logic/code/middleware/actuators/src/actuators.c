#include "actuators.h"
#include <string.h>

static const ActuatorDesc_t *table = NULL;
static size_t count = 0;

void actuators_init(void)
{
    table = actuators_get_table(&count);

    for (size_t i = 0; i < count; i++)
        if (table[i].init)
            table[i].init();
}

void actuators_write(const char *name, const void *data)
{
    for (size_t i = 0; i < count; i++)
        if (strcmp(table[i].name, name) == 0)
        {
            table[i].write(data);
            return;
        }
}
