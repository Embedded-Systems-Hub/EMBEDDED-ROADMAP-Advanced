#ifndef HAL_TEMP_SENSOR_H
#define HAL_TEMP_SENSOR_H

#include <stdint.h>

typedef struct
{
    int      (*init)(void *dev);
    uint16_t (*read_raw)(void *dev);

} HAL_TempSensor_Driver_t;

int      hal_temp_sensor_init(void *dev);
uint16_t hal_temp_sensor_read(void *dev);

const HAL_TempSensor_Driver_t* hal_temp_get_drv(void);

#endif
