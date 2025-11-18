#include "hal_ldr.h"
#include "hal_adc.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct { void *adc_ctx; uint8_t channel; } HAL_Ldr_Device_t;

static int ldr_init_wrapper(void *dev)
{
    HAL_Ldr_Device_t *d = dev;

#ifdef TARGET_HOST
    printf("[LDR_CFG] init dev=%p adc_ctx=%p channel=%u\n",
           d, d->adc_ctx, d->channel);
#endif

    return hal_adc_init(d->adc_ctx, d->channel);
}

static uint16_t ldr_read_wrapper(void *dev)
{
    HAL_Ldr_Device_t *d = dev;

#ifdef TARGET_HOST
    uint16_t raw = rand() % 4096;
    printf("[LDR_CFG] read dev=%p adc_ctx=%p channel=%u -> %u\n",
           d, d->adc_ctx, d->channel, raw);
    return raw;
#else
    return hal_adc_read_raw(d->adc_ctx, d->channel);
#endif
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
