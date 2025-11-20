#include "hal_adc.h"
#include <stdio.h>

static const HAL_Adc_Driver_t *s_drv = NULL;

int hal_adc_init(void *ctx, uint8_t channel)
{
    s_drv = hal_adc_get_drv();
    return s_drv ? s_drv->init(ctx, channel) : -1;
}

uint16_t hal_adc_read_raw(void *ctx, uint8_t channel)
{
    return s_drv ? s_drv->read_raw(ctx, channel) : 0;
}
