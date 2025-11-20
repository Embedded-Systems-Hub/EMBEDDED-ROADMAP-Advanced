#include "hal_led.h"
#include <stdio.h>

static const HAL_LED_Driver_t *s_drv = NULL;

int hal_led_init(void *dev)
{
    s_drv = hal_led_get_drv();
    return s_drv && s_drv->init ? s_drv->init(dev) : -1;
}

int hal_led_write(void *dev, uint8_t on)
{
    return s_drv && s_drv->set_state ? s_drv->set_state(dev, on) : -1;
}
