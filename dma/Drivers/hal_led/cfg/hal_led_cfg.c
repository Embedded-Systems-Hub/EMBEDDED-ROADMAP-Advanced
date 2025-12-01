#include "hal_led.h"
#include "hal_pwm.h"

typedef struct { void *pwm_ctx; uint8_t channel; void *data; } HAL_Led_Device_t;

static status_t led_pwm_init_wrapper(void *dev)
{
	HAL_Led_Device_t *d = (HAL_Led_Device_t *)dev;

    CHECK_NULL(d);
    CHECK_NULL(d->pwm_ctx);

    CHECK_STATUS(hal_pwm_init(d->pwm_ctx, d->channel, d->data));

    return STATUS_OK;
}

static status_t led_pwm_set_wrapper(void *dev, const void *in)
{
	HAL_Led_Device_t *d = (HAL_Led_Device_t *)dev;

    CHECK_NULL(d);
    CHECK_NULL(d->pwm_ctx);
    CHECK_NULL(in);

    CHECK_STATUS(hal_pwm_set(d->pwm_ctx, in));

    return STATUS_OK;
}

static const HAL_LED_Driver_t led_driver =
{
    .init = led_pwm_init_wrapper,
    .set = led_pwm_set_wrapper
};

const HAL_LED_Driver_t* hal_led_get_drv(void)
{
    return &led_driver;
}
