#include "hal_adc.h"
#include "error_codes.h"

static const HAL_Adc_Driver_t *s_drv = NULL;

status_t hal_adc_init(void *ctx, uint8_t channel)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);

    s_drv = hal_adc_get_drv();
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->init);

    CHECK_STATUS(s_drv->init(ctx, channel));

    return ret;
}

status_t hal_adc_read_raw(void *ctx, uint8_t channel, uint16_t *out_raw)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(out_raw);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->read_raw);

    CHECK_STATUS(s_drv->read_raw(ctx, channel, out_raw));

    return ret;
}
