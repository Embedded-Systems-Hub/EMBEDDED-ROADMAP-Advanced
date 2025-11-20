#ifndef HAL_FAN_H
#define HAL_FAN_H

#include <stdint.h>

typedef struct
{
    int (*init)(void *dev);
    int (*set_state)(void *dev, uint8_t val);

} HAL_Fan_Driver_t;

int hal_fan_init(void *dev);
int hal_fan_write(void *dev, uint8_t val);

const HAL_Fan_Driver_t* hal_fan_get_drv(void);

#endif
