#include "sensors.h"
#include <string.h>
#include <stdio.h>

static const SensorDesc_t *s_table = NULL;
static size_t s_count = 0;

status_t sensors_init(void)
{
    s_table = sensors_get_table(&s_count);

	CHECK_NULL(s_table);

    for (size_t i = 0; i < s_count; i++)
    {
    	CHECK_NULL(s_table[i].init);
    	CHECK_STATUS(s_table[i].init());
    }

    return STATUS_OK;
}

status_t sensors_read(const char *name, void *out)
{
    CHECK_NULL(name);
    CHECK_NULL(out);

    for (size_t i = 0; i < s_count; i++)
    {
        if (strcmp(s_table[i].name, name) == 0)
        {
        	CHECK_NULL(s_table[i].read);
        	CHECK_STATUS(s_table[i].read(out));
        }
    }

    return STATUS_OK;
}
