#include "hal_gpio.h"
#include <stdio.h>

static const HAL_GPIO_Driver_t *s_drv = NULL;

int hal_gpio_init(void *ctx, uint8_t pin, HAL_GPIO_Direction_t dir)
{
    s_drv = hal_gpio_get_drv();
    return s_drv->init(ctx, pin, dir);
}

int hal_gpio_write(void *ctx, uint8_t pin, uint8_t value)
{
    return s_drv->write(ctx, pin, value);
}

int hal_gpio_read(void *ctx, uint8_t pin, uint8_t *value)
{
    return s_drv->read(ctx, pin, value);
}
