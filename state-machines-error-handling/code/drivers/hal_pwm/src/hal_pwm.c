#include "hal_pwm.h"
#include "error_codes.h"

static const HAL_PWM_Driver_t *s_drv = NULL;

status_t hal_pwm_init(void *ctx, uint8_t channel)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);

    if (s_drv == NULL)
    {
        s_drv = hal_pwm_get_drv();
        CHECK_NULL(s_drv);
        CHECK_NULL(s_drv->init);
    }

    CHECK_STATUS(s_drv->init(ctx, channel));

    return ret;
}

status_t hal_pwm_set(void *ctx, uint8_t channel, uint8_t duty_percent)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);

    if (s_drv == NULL)
    {
        s_drv = hal_pwm_get_drv();
        CHECK_NULL(s_drv);
        CHECK_NULL(s_drv->set);
    }

    if (duty_percent > 100U)
    {
        ret = STATUS_ERR_OUT_OF_RANGE;
    }
    else
    {
        CHECK_STATUS(s_drv->set(ctx, channel, duty_percent));
    }

    return ret;
}
