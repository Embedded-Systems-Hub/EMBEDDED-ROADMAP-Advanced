#ifndef HAL_LED_H
#define HAL_LED_H

#include <stdio.h>
#include <stdint.h>
#include "error_codes.h"

typedef struct
{
    status_t (*init)(void *dev);
    status_t (*set_state)(void *dev, uint8_t on);
} HAL_LED_Driver_t;

status_t hal_led_init(void *dev);
status_t hal_led_write(void *dev, uint8_t on);

const HAL_LED_Driver_t* hal_led_get_drv(void);

#endif
