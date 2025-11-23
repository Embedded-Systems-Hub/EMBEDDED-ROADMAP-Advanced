#ifndef HAL_TEMP_SENSOR_H
#define HAL_TEMP_SENSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "error_codes.h"

typedef struct
{
    status_t (*init)(void *dev);
    status_t (*read_raw)(void *dev, uint16_t *out_raw);
} HAL_TempSensor_Driver_t;

status_t hal_temp_sensor_init(void *dev);
status_t hal_temp_sensor_read(void *dev, uint16_t *out_raw);

const HAL_TempSensor_Driver_t* hal_temp_get_drv(void);

#endif
