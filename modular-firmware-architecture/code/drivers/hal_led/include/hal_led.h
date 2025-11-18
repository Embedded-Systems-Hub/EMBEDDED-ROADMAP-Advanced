#ifndef HAL_LED_H
#define HAL_LED_H

#include <stdint.h>

typedef struct
{
    int (*init)(void *dev);
    int (*set_state)(void *dev, uint8_t on);

} HAL_LED_Driver_t;

int  hal_led_init(void *dev);
int  hal_led_write(void *dev, uint8_t on);

const HAL_LED_Driver_t* hal_led_get_drv(void);

#endif
