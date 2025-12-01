#include "hal_potentiometer.h"
#include "hal_adc.h"
#include "error_codes.h"

typedef struct { void *adc_ctx; uint8_t channel; void *data; } HAL_Potentiometer_Device_t;

static status_t potentiometer_init_wrapper(void *dev)
{
    HAL_Potentiometer_Device_t *d = (HAL_Potentiometer_Device_t *)dev;

    CHECK_NULL(d);
    CHECK_NULL(d->adc_ctx);

    CHECK_STATUS(hal_adc_init(d->adc_ctx, d->channel, d->data));

    return STATUS_OK;
}

static status_t potentiometer_read_wrapper(void *dev, void *out)
{
    HAL_Potentiometer_Device_t *d = (HAL_Potentiometer_Device_t *)dev;

    CHECK_NULL(d);
    CHECK_NULL(d->adc_ctx);
    CHECK_NULL(out);

    CHECK_STATUS(hal_adc_read(d->adc_ctx, out));

    return STATUS_OK;
}

static const HAL_Potentiometer_Driver_t potentiometer_driver =
{
    .init     = potentiometer_init_wrapper,
    .read = potentiometer_read_wrapper
};

const HAL_Potentiometer_Driver_t* hal_potentiometer_get_drv(void)
{
    return &potentiometer_driver;
}
