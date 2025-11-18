#include "hal_ldr.h"
#include <stdio.h>

static const HAL_Ldr_Driver_t *s_drv = NULL;

int hal_ldr_init(void *dev)
{
    s_drv = hal_ldr_get_drv();
    return s_drv && s_drv->init ? s_drv->init(dev) : -1;
}

uint16_t hal_ldr_read(void *dev)
{
    return s_drv && s_drv->read_raw ? s_drv->read_raw(dev) : 0;
}
