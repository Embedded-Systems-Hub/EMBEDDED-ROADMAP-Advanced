#include "hal_fan.h"
#include <stdio.h>

static const HAL_Fan_Driver_t *s_drv = NULL;

int hal_fan_init(void *dev)
{
    s_drv = hal_fan_get_drv();
    return s_drv && s_drv->init ? s_drv->init(dev) : -1;
}

int hal_fan_write(void *dev, uint8_t val)
{
    return s_drv && s_drv->set_state ? s_drv->set_state(dev, val) : -1;
}
