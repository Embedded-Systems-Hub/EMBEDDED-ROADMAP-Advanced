#include "hal_temp_sensor.h"
#include <stdio.h>

static const HAL_TempSensor_Driver_t *s_drv = NULL;

int hal_temp_sensor_init(void *dev)
{
    s_drv = hal_temp_get_drv();
    return s_drv && s_drv->init ? s_drv->init(dev) : -1;
}

uint16_t hal_temp_sensor_read(void *dev)
{
    return s_drv && s_drv->read_raw ? s_drv->read_raw(dev) : 0;
}
