#include "hal_fan.h"
#include "hal_pwm.h"
#include <stdio.h>

typedef struct { void *pwm_ctx; uint8_t channel; } HAL_Fan_Device_t;

static int fan_init_wrapper(void *dev)
{
    HAL_Fan_Device_t *d = dev;

#ifdef TARGET_HOST
    printf("[FAN_CFG] init dev=%p port=%p channel=%u\n",
           d, d->pwm_ctx, d->channel);
#endif

    return hal_pwm_init(d->pwm_ctx, d->channel);
}

static int fan_set_state_wrapper(void *dev, uint8_t speed)
{
    HAL_Fan_Device_t *d = dev;

    uint8_t duty = 0;

    if (speed == 1)
        duty = 50;  // LOW
    else if (speed >= 2)
        duty = 100; // HIGH

#ifdef TARGET_HOST
    printf(" * [FAN_CFG] speed=%u → duty=%u%%\n", speed, duty);
#endif

    return hal_pwm_set(d->pwm_ctx, d->channel, duty);
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