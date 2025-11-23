#ifndef HAL_PWM_H
#define HAL_PWM_H

#include <stdio.h>
#include <stdint.h>
#include "error_codes.h"

typedef struct
{
    status_t (*init)(void *ctx, uint8_t channel);
    status_t (*set)(void *ctx, uint8_t channel, uint8_t duty_percent);

} HAL_PWM_Driver_t;

status_t hal_pwm_init(void *ctx, uint8_t channel);
status_t hal_pwm_set(void *ctx, uint8_t channel, uint8_t duty_percent);

const HAL_PWM_Driver_t* hal_pwm_get_drv(void);

#endif
