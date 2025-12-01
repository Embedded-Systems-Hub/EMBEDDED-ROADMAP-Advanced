#ifndef HAL_PWM_H
#define HAL_PWM_H

#include <stdio.h>
#include <stdint.h>
#include "error_codes.h"

typedef struct
{
    status_t (*init)(void *ctx, uint8_t channel);
    status_t (*set)(void *ctx, const void *in);
} HAL_PWM_Driver_t;

status_t hal_pwm_init(void *ctx, uint8_t channel);
status_t hal_pwm_set(void *ctx, const void *in);

const HAL_PWM_Driver_t* hal_pwm_get_drv(void);

#endif
