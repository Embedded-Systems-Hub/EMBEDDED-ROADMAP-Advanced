#ifndef HAL_PWM_H
#define HAL_PWM_H

#include <stdint.h>

typedef struct
{
    int (*init)(void *ctx, uint8_t channel);
    int (*set)(void *ctx, uint8_t channel, uint8_t duty_percent);
} HAL_PWM_Driver_t;

int hal_pwm_init(void *ctx, uint8_t channel);
int hal_pwm_set(void *ctx, uint8_t channel, uint8_t duty_percent);

const HAL_PWM_Driver_t* hal_pwm_get_drv(void);

#endif
