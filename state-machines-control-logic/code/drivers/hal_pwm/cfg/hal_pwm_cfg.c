#include "hal_pwm.h"
#include <stdio.h>

static int pwm_init_wrapper(void *ctx, uint8_t channel)
{
#ifdef TARGET_HOST
    printf("[PWM_CFG] init ctx=%p channel=%u\n", ctx, channel);
#endif
    return 0;
}

static int pwm_set_wrapper(void *ctx, uint8_t channel, uint8_t duty_percent)
{
#ifdef TARGET_HOST
    printf("[PWM_CFG] write ctx=%p channel=%u duty=%u%%\n", ctx, channel, duty_percent);
#endif
    return 0;
}

static const HAL_PWM_Driver_t pwm_driver =
{
    .init  = pwm_init_wrapper,
    .set = pwm_set_wrapper
};

const HAL_PWM_Driver_t* hal_pwm_get_drv(void)
{
    return &pwm_driver;
}
