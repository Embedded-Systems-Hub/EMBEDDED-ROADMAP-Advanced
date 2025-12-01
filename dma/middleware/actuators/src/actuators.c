#include "actuators.h"
#include <string.h>

static const ActuatorDesc_t *a_table = NULL;
static size_t a_count = 0;

status_t actuators_init(void)
{
	a_table = actuators_get_table(&a_count);

	CHECK_NULL(a_table);

    for (size_t i = 0; i < a_count; i++)
    {
    	CHECK_NULL(a_table[i].init);
    	CHECK_STATUS(a_table[i].init());
    }

    return STATUS_OK;
}

status_t actuators_write(const char *name, const void *in)
{
    CHECK_NULL(name);
    CHECK_NULL(in);

    for (size_t i = 0; i < a_count; i++)
    {
        if (strcmp(a_table[i].name, name) == 0)
        {
        	CHECK_NULL(a_table[i].write);
        	CHECK_STATUS(a_table[i].write(in));
        }
    }

    return STATUS_OK;
}
