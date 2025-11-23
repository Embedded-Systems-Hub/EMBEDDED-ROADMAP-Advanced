#include "hal_pwm.h"
#include "error_codes.h"

static status_t pwm_init_wrapper(void *ctx, uint8_t channel)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);

#ifdef TARGET_HOST
    printf("[PWM_CFG] init ctx=%p channel=%u\n", ctx, channel);
#endif

    return ret;
}

static status_t pwm_set_wrapper(void *ctx, uint8_t channel, uint8_t duty_percent)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);

#ifdef TARGET_HOST
    printf("[PWM_CFG] write ctx=%p channel=%u duty=%u%%\n",
           ctx, channel, duty_percent);
#endif

    return ret;
}

static const HAL_PWM_Driver_t pwm_driver =
{
    .init = pwm_init_wrapper,
    .set  = pwm_set_wrapper
};

const HAL_PWM_Driver_t* hal_pwm_get_drv(void)
{
    return &pwm_driver;
}
