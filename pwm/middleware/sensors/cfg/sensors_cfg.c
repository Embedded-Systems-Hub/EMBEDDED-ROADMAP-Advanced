#include <stdio.h>
#include "sensors.h"
#include "interfaces.h"
#include "hal_potentiometer.h"

typedef struct { const void *adc_ctx; uint8_t channel; } Potentiometer_Device_t;

static Potentiometer_Device_t pot_dev;

static status_t potentiometer_init_wrapper(void)
{
	status_t ret  = interfaces_get("adc_pot", &pot_dev.adc_ctx);
    pot_dev.channel  = 0U;

    CHECK_NULL(pot_dev.adc_ctx);
    CHECK_STATUS(hal_potentiometer_init(&pot_dev));

    return ret;
}

static status_t potentiometer_read_wrapper(void *out)
{
	CHECK_NULL(out);

	uint16_t *value = (uint16_t*)out;
	CHECK_STATUS(hal_potentiometer_read(&pot_dev, (uint16_t*)out));

	*value = ((*value * 100) / 4095);

    return STATUS_OK;
}

static SensorDesc_t sensor_table[] =
{
    { "potentiometer_percent", potentiometer_init_wrapper, potentiometer_read_wrapper }
};

const SensorDesc_t* sensors_get_table(size_t *count)
{
    *count = sizeof(sensor_table) / sizeof(sensor_table[0]);
    return sensor_table;
}
