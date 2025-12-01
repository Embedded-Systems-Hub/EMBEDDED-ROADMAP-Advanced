#include <stdio.h>
#include "actuators.h"
#include "interfaces.h"
#include "hal_led.h"

typedef struct { const void *pwm_ctx; uint8_t channel; } Led_Device_t;

static Led_Device_t led_dev;

static status_t light_init_wrapper(void)
{
	status_t ret  = interfaces_get("pwm_led", &led_dev.pwm_ctx);
    led_dev.channel  = 1U;

    CHECK_NULL(led_dev.pwm_ctx);
    CHECK_STATUS(hal_led_init(&led_dev));

    return ret;
}

static status_t light_write_wrapper(const void *in)
{
	CHECK_NULL(in);

	uint32_t value = *(const uint32_t *)in;
	value = (value * 4095) / 100U;

    CHECK_STATUS(hal_led_write(&led_dev, &value));

    return STATUS_OK;
}

static ActuatorDesc_t table[] =
{
    { "led_percent", light_init_wrapper, light_write_wrapper  }
};

const ActuatorDesc_t* actuators_get_table(size_t *count)
{
    *count = sizeof(table)/sizeof(table[0]);
    return table;
}
