#include "hal_spi.h"
#include "error_codes.h"

static const HAL_SPI_Driver_t *s_drv = NULL;

status_t hal_spi_init(void *ctx)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);

    s_drv = hal_spi_get_drv();
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->init);

    CHECK_STATUS(s_drv->init(ctx));

    return ret;
}

status_t hal_spi_write(void *ctx, const uint8_t *data, size_t len)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(data);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->write);

    CHECK_STATUS(s_drv->write(ctx, data, len));

    return ret;
}

status_t hal_spi_read(void *ctx, uint8_t *data, size_t len)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(data);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->read);

    CHECK_STATUS(s_drv->read(ctx, data, len));

    return ret;
}

status_t hal_spi_transfer(void *ctx, const uint8_t *tx, uint8_t *rx, size_t len)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(tx);
    CHECK_NULL(rx);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->transfer);

    CHECK_STATUS(s_drv->transfer(ctx, tx, rx, len));

    return ret;
}

status_t hal_spi_cs_low(void *ctx, uint8_t cs_pin)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->cs_low);

    CHECK_STATUS(s_drv->cs_low(ctx, cs_pin));

    return ret;
}

status_t hal_spi_cs_high(void *ctx, uint8_t cs_pin)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->cs_high);

    CHECK_STATUS(s_drv->cs_high(ctx, cs_pin));

    return ret;
}
