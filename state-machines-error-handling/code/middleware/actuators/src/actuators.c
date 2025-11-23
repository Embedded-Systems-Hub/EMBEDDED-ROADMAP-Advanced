#include "actuators.h"
#include "error_codes.h"

#include <stdio.h>
#include <string.h>

/* Pointer to the statically defined actuator descriptor table. */
static const ActuatorDesc_t *actuators_desc_table = NULL;

/* Number of entries in the descriptor table. */
static size_t actuators_desc_count = 0U;

status_t actuators_init(void)
{
    status_t ret = STATUS_OK;

    /*
     * Obtain the statically defined actuator descriptor table.
     * The table is provided by actuators_cfg.
     */
    actuators_desc_table = actuators_get_table(&actuators_desc_count);
    CHECK_NULL(actuators_desc_table);

    /* Initialize the actuators one by one. */
    for (size_t i = 0; i < actuators_desc_count; i++)
    {
        if (actuators_desc_table[i].init != NULL)
        {
            /* Actuator-specific initialization logic. */
            CHECK_STATUS(actuators_desc_table[i].init());
        }
    }

    return ret;
}

status_t actuators_write(const char *name, const void *data)
{
    status_t ret = STATUS_OK;
    const ActuatorDesc_t *desc = NULL;

    /* Parameter checks. */
    CHECK_NULL(name);
    CHECK_NULL(data);

    /* Linear search in the actuator table. */
    for (size_t i = 0; i < actuators_desc_count; i++)
    {
        if (strcmp(actuators_desc_table[i].name, name) == 0)
        {
            desc = &actuators_desc_table[i];
            break;
        }
    }

    /* If the actuator name was not found. */
    if (desc == NULL)
    {
        return STATUS_ERR_INVALID_PARAM;
    }

    /*
     * If the entry exists but the write function is missing,
     * the actuator was declared but not properly implemented.
     */
    if (desc->write == NULL)
    {
        return STATUS_ERR_UNINIT;
    }

    /* Delegate the write to the actuator-specific implementation. */
    CHECK_STATUS(desc->write(data));

    return ret;
}
