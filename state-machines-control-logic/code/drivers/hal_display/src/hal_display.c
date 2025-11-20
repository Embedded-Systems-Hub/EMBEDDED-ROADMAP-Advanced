#include "hal_display.h"
#include <stdio.h>

static const HAL_Display_Driver_t *s_drv = NULL;

int hal_display_init(void *dev)
{
    s_drv = hal_display_get_drv();
    return s_drv && s_drv->init ? s_drv->init(dev) : -1;
}

int hal_display_write(void *dev, const uint8_t *data, size_t len)
{
    return s_drv && s_drv->write ? s_drv->write(dev, data, len) : -1;
}
