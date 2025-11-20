#include "hal_adc.h"
#include <stdio.h>
#include <stdlib.h>

static int adc_init_wrapper(void *ctx, uint8_t channel)
{
#ifdef TARGET_HOST
    printf("[ADC_CFG] init ctx=%p channel=%u\n", ctx, channel);
#endif

    return 0;
}

static uint16_t adc_read_raw_wrapper(void *ctx, uint8_t channel)
{
#ifdef TARGET_HOST
    printf("[ADC_CFG] read_raw ctx=%p channel=%u -> simulated\n",
           ctx, channel);
    return rand() % 4096;
#else
    return 1234;
#endif
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
