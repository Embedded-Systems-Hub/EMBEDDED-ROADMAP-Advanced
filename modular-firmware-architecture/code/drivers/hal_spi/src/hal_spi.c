#include "hal_spi.h"
#include <stdio.h>

static const HAL_SPI_Driver_t *s_drv = NULL;

int hal_spi_init(void *ctx)
{
    s_drv = hal_spi_get_drv();
    return s_drv ? s_drv->init(ctx) : -1;
}

int hal_spi_write(void *ctx, const uint8_t *data, size_t len)
{
    return s_drv ? s_drv->write(ctx, data, len) : -1;
}

int hal_spi_read(void *ctx, uint8_t *data, size_t len)
{
    return s_drv ? s_drv->read(ctx, data, len) : -1;
}

int hal_spi_transfer(void *ctx, const uint8_t *tx, uint8_t *rx, size_t len)
{
    return s_drv ? s_drv->transfer(ctx, tx, rx, len) : -1;
}

int hal_spi_cs_low(void *ctx, uint8_t cs_pin)
{
    return s_drv ? s_drv->cs_low(ctx, cs_pin) : -1;
}

int hal_spi_cs_high(void *ctx, uint8_t cs_pin)
{
    return s_drv ? s_drv->cs_high(ctx, cs_pin) : -1;
}
