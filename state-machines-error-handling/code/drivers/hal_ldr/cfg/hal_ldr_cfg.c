#include "hal_ldr.h"
#include "hal_adc.h"
#include "error_codes.h"
#include <stdlib.h>

typedef struct { void *adc_ctx; uint8_t channel; } HAL_Ldr_Device_t;

static status_t ldr_init_wrapper(void *dev)
{
    status_t ret = STATUS_OK;
    HAL_Ldr_Device_t *d = dev;

    CHECK_NULL(d);
    CHECK_NULL(d->adc_ctx);

#ifdef TARGET_HOST
    printf("[LDR_CFG] init dev=%p adc_ctx=%p channel=%u\n",
           d, d->adc_ctx, d->channel);
#endif

    CHECK_STATUS(hal_adc_init(d->adc_ctx, d->channel));

    return ret;
}

static status_t ldr_read_wrapper(void *dev, uint16_t *out_raw)
{
    status_t ret = STATUS_OK;
    HAL_Ldr_Device_t *d = dev;

    CHECK_NULL(d);
    CHECK_NULL(d->adc_ctx);
    CHECK_NULL(out_raw);

#ifdef TARGET_HOST
    uint16_t raw12 = (uint16_t)(rand() % 4096);
    printf("[LDR_CFG] read dev=%p adc_ctx=%p channel=%u -> %u\n",
           d, d->adc_ctx, d->channel, raw12);
    *out_raw = raw12;
#else
    CHECK_STATUS(hal_adc_read_raw(d->adc_ctx, d->channel, out_raw));
#endif

    return ret;
}

static const HAL_Ldr_Driver_t ldr_driver =
{
    .init     = ldr_init_wrapper,
    .read_raw = ldr_read_wrapper
};

const HAL_Ldr_Driver_t* hal_ldr_get_drv(void)
{
    return &ldr_driver;
}
