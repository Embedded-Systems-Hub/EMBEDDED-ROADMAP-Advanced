#ifndef HAL_FAN_H
#define HAL_FAN_H

#include <stdio.h>
#include <stdint.h>
#include "error_codes.h"

typedef struct
{
    status_t (*init)(void *dev);
    status_t (*set_state)(void *dev, uint8_t val);

} HAL_Fan_Driver_t;

status_t hal_fan_init(void *dev);
status_t hal_fan_write(void *dev, uint8_t val);

const HAL_Fan_Driver_t* hal_fan_get_drv(void);

#endif
