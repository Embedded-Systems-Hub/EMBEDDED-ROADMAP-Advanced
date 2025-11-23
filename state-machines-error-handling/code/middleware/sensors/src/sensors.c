#include "sensors.h"
#include "error_codes.h"

#include <string.h>
#include <stdio.h>

/* Static descriptor table (populated during init). */
static const SensorDesc_t *sensors_desc_table = NULL;

/* Number of sensor entries in the descriptor table. */
static size_t sensors_desc_count = 0U;

status_t sensors_init(void)
{
    status_t ret = STATUS_OK;

    /* Obtain the statically defined sensor descriptor table. */
    sensors_desc_table = sensors_get_table(&sensors_desc_count);
    CHECK_NULL(sensors_desc_table);

    /* Initialize the sensors. */
    for (size_t i = 0U; i < sensors_desc_count; i++)
    {
        if (sensors_desc_table[i].init != NULL)
        {
            CHECK_STATUS(sensors_desc_table[i].init());
        }
    }

    return ret;
}

status_t sensors_read(const char *name, float *out_value)
{
    status_t ret = STATUS_OK;
    const SensorDesc_t *desc = NULL;

    /* Parameter checks. */
    CHECK_NULL(name);
    CHECK_NULL(out_value);

    /* Linear search in the sensor table. */
    for (size_t i = 0U; i < sensors_desc_count; i++)
    {
        if (strcmp(sensors_desc_table[i].name, name) == 0)
        {
            desc = &sensors_desc_table[i];
            break;
        }
    }

    /* If the sensor name was not found, the caller provided an invalid id. */
    if (desc == NULL)
    {
        return STATUS_ERR_INVALID_PARAM;
    }

    /*
     * If the entry exists but the read function is missing,
     * the sensor was declared but not properly initialized or implemented.
     */
    if (desc->read == NULL)
    {
        return STATUS_ERR_UNINIT;
    }

    /* Delegate reading to the sensor-specific implementation. */
    CHECK_STATUS(desc->read(out_value));

    return ret;
}
