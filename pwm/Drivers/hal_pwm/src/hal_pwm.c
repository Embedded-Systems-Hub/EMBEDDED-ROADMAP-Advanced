#include "hal_pwm.h"

static const HAL_PWM_Driver_t *s_drv = NULL;

status_t hal_pwm_init(void *ctx, uint8_t channel)
{
    s_drv = hal_pwm_get_drv();
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->init);
    CHECK_NULL(ctx);

    CHECK_STATUS(s_drv->init(ctx, channel));

    return STATUS_OK;
}

status_t hal_pwm_set(void *ctx, const void *in)
{
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->set);
    CHECK_NULL(ctx);

    CHECK_STATUS(s_drv->set(ctx, in));

    return STATUS_OK;
}
