#include "hal_adc.h"
#include "error_codes.h"
#include <stdlib.h>

static status_t adc_init_wrapper(void *ctx, uint8_t channel)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);

#ifdef TARGET_HOST
    printf("[ADC_CFG] init ctx=%p channel=%u\n", ctx, channel);
#endif

    return ret;
}

static status_t adc_read_raw_wrapper(void *ctx, uint8_t channel, uint16_t *out_raw)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(out_raw);

#ifdef TARGET_HOST
    printf("[ADC_CFG] read_raw ctx=%p channel=%u -> simulated\n",
           ctx, channel);
    *out_raw = (uint16_t)(rand() % 4096);
#else
    *out_raw = 1234U;
#endif

    return ret;
}

static const HAL_Adc_Driver_t adc_driver =
{
    .init     = adc_init_wrapper,
    .read_raw = adc_read_raw_wrapper
};

const HAL_Adc_Driver_t* hal_adc_get_drv(void)
{
    return &adc_driver;
}
