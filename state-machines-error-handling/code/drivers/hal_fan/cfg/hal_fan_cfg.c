#include "hal_fan.h"
#include "hal_pwm.h"
#include "error_codes.h"

typedef struct
{
    void *pwm_ctx;
    uint8_t channel;
} HAL_Fan_Device_t;

static status_t fan_init_wrapper(void *dev)
{
    status_t ret = STATUS_OK;
    HAL_Fan_Device_t *d = dev;

    CHECK_NULL(d);
    CHECK_NULL(d->pwm_ctx);

#ifdef TARGET_HOST
    printf("[FAN_CFG] init dev=%p pwm=%p channel=%u\n",
           d, d->pwm_ctx, d->channel);
#endif

    CHECK_STATUS(hal_pwm_init(d->pwm_ctx, d->channel));

    return ret;
}

static status_t fan_set_state_wrapper(void *dev, uint8_t speed)
{
    status_t ret = STATUS_OK;
    HAL_Fan_Device_t *d = dev;

    uint8_t duty = 0U;

    CHECK_NULL(d);
    CHECK_NULL(d->pwm_ctx);

    /* Speed mapping: OFF / LOW / HIGH */
    if (speed == 1U)
    {
        duty = 50U;
    }
    else if (speed >= 2U)
    {
        duty = 100U;
    }
    else
    {
        duty = 0U;
    }

#ifdef TARGET_HOST
    printf(" * [FAN_CFG] speed=%u => duty=%u%%\n", speed, duty);
#endif

    CHECK_STATUS(hal_pwm_set(d->pwm_ctx, d->channel, duty));

    return ret;
}

static const HAL_Fan_Driver_t fan_driver =
{
    .init      = fan_init_wrapper,
    .set_state = fan_set_state_wrapper
};

const HAL_Fan_Driver_t* hal_fan_get_drv(void)
{
    return &fan_driver;
}