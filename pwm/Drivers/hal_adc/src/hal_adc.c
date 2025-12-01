#include "hal_adc.h"

static const HAL_Adc_Driver_t *s_drv = NULL;

status_t hal_adc_init(void *ctx, uint8_t channel)
{
    s_drv = hal_adc_get_drv();
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->init);
    CHECK_NULL(ctx);

    CHECK_STATUS(s_drv->init(ctx, channel));

    return STATUS_OK;
}

status_t hal_adc_read(void *ctx, void *out)
{
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->read);
    CHECK_NULL(ctx);
    CHECK_NULL(out);

    CHECK_STATUS(s_drv->read(ctx, out));

    return STATUS_OK;
}
