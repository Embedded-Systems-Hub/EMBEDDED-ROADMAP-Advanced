#include "hal_led.h"
#include "hal_gpio.h"
#include "error_codes.h"

typedef struct { void *gpio_ctx; uint8_t pin; } HAL_Led_Device_t;

static status_t led_init_wrapper(void *dev)
{
    status_t ret = STATUS_OK;
    HAL_Led_Device_t *d = dev;

    CHECK_NULL(d);
    CHECK_NULL(d->gpio_ctx);

#ifdef TARGET_HOST
    printf("[LED_CFG] init dev=%p port=%p pin=%u\n",
           d, d->gpio_ctx, d->pin);
#endif

    CHECK_STATUS(hal_gpio_init(d->gpio_ctx, d->pin, HAL_GPIO_DIR_OUTPUT));

    return ret;
}

static status_t led_set_state_wrapper(void *dev, uint8_t on)
{
    status_t ret = STATUS_OK;
    HAL_Led_Device_t *d = dev;

    CHECK_NULL(d);
    CHECK_NULL(d->gpio_ctx);

#ifdef TARGET_HOST
    printf("[LED_CFG] write dev=%p port=%p pin=%u val=%u\n",
           d, d->gpio_ctx, d->pin, on);
#endif

    CHECK_STATUS(hal_gpio_write(d->gpio_ctx, d->pin, on));

    return ret;
}

static const HAL_LED_Driver_t led_driver =
{
    .init      = led_init_wrapper,
    .set_state = led_set_state_wrapper
};

const HAL_LED_Driver_t* hal_led_get_drv(void)
{
    return &led_driver;
}
