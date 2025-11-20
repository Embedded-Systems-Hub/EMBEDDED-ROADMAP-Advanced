#include "hal_pwm.h"
#include <stdio.h>

static const HAL_PWM_Driver_t *s_drv = NULL;

int hal_pwm_init(void *ctx, uint8_t channel)
{
    if (!s_drv)
        s_drv = hal_pwm_get_drv();

    return s_drv->init(ctx, channel);
}

int hal_pwm_set(void *ctx, uint8_t channel, uint8_t duty_percent)
{
    if (!s_drv)
        s_drv = hal_pwm_get_drv();

    return s_drv->set(ctx, channel, duty_percent);
}
