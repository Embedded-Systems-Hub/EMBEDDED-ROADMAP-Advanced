#ifndef HAL_LED_H
#define HAL_LED_H

#include <stdint.h>
#include "error_codes.h"

typedef struct
{
	status_t (*init)(void *dev);
    status_t (*set)(void *dev, const void *in);

} HAL_LED_Driver_t;

status_t hal_led_init(void *dev);
status_t hal_led_write(void *dev, const void *in);

const HAL_LED_Driver_t* hal_led_get_drv(void);

#endif
