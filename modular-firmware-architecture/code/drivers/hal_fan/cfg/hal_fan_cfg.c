#include "hal_fan.h"
#include "hal_gpio.h"
#include <stdio.h>

typedef struct { void *gpio_ctx; uint8_t pin; } HAL_Fan_Device_t;

static int fan_init_wrapper(void *dev)
{
    HAL_Fan_Device_t *d = dev;

#ifdef TARGET_HOST
    printf("[FAN_CFG] init dev=%p port=%p pin=%u\n",
           d, d->gpio_ctx, d->pin);
#endif

    return hal_gpio_init(d->gpio_ctx, d->pin, HAL_GPIO_DIR_OUTPUT);
}

static int fan_set_state_wrapper(void *dev, uint8_t val)
{
    HAL_Fan_Device_t *d = dev;

#ifdef TARGET_HOST
    printf("[FAN_CFG] write dev=%p port=%p pin=%u val=%u\n",
           d, d->gpio_ctx, d->pin, val);
#endif

    return hal_gpio_write(d->gpio_ctx, d->pin, val);
}

static const HAL_Fan_Driver_t fan_driver =
{
    .init      = fan_init_wrapper,
    .set_state = fan_set_state_wrapper
};

const HAL_Fan_Driver_t* hal_fan_get_drv(void)
{
    return &fan_driver;
}