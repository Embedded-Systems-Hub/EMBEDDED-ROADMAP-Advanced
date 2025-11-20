#include "hal_led.h"
#include "hal_gpio.h"
#include <stdio.h>

typedef struct { void *gpio_ctx; uint8_t pin; } HAL_Led_Device_t;

static int led_init_wrapper(void *dev)
{
    HAL_Led_Device_t *d = dev;

#ifdef TARGET_HOST
    printf("[LED_CFG] init dev=%p port=%p pin=%u\n",
           d, d->gpio_ctx, d->pin);
#endif

    return hal_gpio_init(d->gpio_ctx, d->pin, HAL_GPIO_DIR_OUTPUT);
}

static int led_set_state_wrapper(void *dev, uint8_t on)
{
    HAL_Led_Device_t *d = dev;

#ifdef TARGET_HOST
    printf("[LED_CFG] write dev=%p port=%p pin=%u val=%u\n",
           d, d->gpio_ctx, d->pin, on);
#endif

    return hal_gpio_write(d->gpio_ctx, d->pin, on);
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
