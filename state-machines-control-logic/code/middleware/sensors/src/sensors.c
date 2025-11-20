#include "sensors.h"
#include <string.h>
#include <stdio.h>

static const SensorDesc_t *s_table = NULL;
static size_t s_count = 0;

void sensors_init(void)
{
    s_table = sensors_get_table(&s_count);

    for (size_t i = 0; i < s_count; i++)
        if (s_table[i].init)
            s_table[i].init();
}

float sensors_read(const char *name)
{
    for (size_t i = 0; i < s_count; i++)
        if (strcmp(s_table[i].name, name) == 0)
            return s_table[i].read();

    return -999.0f;
}
