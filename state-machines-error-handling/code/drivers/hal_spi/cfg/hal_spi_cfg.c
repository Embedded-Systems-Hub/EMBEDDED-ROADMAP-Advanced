#include "hal_spi.h"
#include "error_codes.h"

static status_t spi_init_wrapper(void *ctx)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);

#ifdef TARGET_HOST
    printf("[SPI_CFG] init ctx=%p\n", ctx);
#endif

    return ret;
}

static status_t spi_write_wrapper(void *ctx, const uint8_t *data, size_t len)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(data);

#ifdef TARGET_HOST
    printf("[SPI_CFG] write ctx=%p len=%zu data=[ ", ctx, len);
    for (size_t i = 0; i < len; i++)
        printf("%02X ", data[i]);
    printf("]\n");
#endif

    return ret;
}

static status_t spi_read_wrapper(void *ctx, uint8_t *data, size_t len)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(data);

#ifdef TARGET_HOST
    printf("[SPI_CFG] read ctx=%p len=%zu\r\n", ctx, len);
#endif

    for (size_t i = 0; i < len; i++)
        data[i] = 0U;

    return ret;
}

static status_t spi_transfer_wrapper(void *ctx, const uint8_t *tx, uint8_t *rx, size_t len)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(tx);
    CHECK_NULL(rx);

#ifdef TARGET_HOST
    printf("[SPI_CFG] transfer ctx=%p len=%zu tx=[ ", ctx, len);
    for (size_t i = 0; i < len; i++)
        printf("%02X ", tx[i]);
    printf("]\n");
#endif

    for (size_t i = 0; i < len; i++)
        rx[i] = 0U;

    return ret;
}

static status_t spi_cs_low_wrapper(void *ctx, uint8_t cs_pin)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);

#ifdef TARGET_HOST
    printf("[SPI_CFG] CS LOW ctx=%p pin=%u\n", ctx, cs_pin);
#endif

    return ret;
}

static status_t spi_cs_high_wrapper(void *ctx, uint8_t cs_pin)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);

#ifdef TARGET_HOST
    printf("[SPI_CFG] CS HIGH ctx=%p pin=%u\n", ctx, cs_pin);
#endif

    return ret;
}

static const HAL_SPI_Driver_t spi_driver =
{
    .init     = spi_init_wrapper,
    .write    = spi_write_wrapper,
    .read     = spi_read_wrapper,
    .transfer = spi_transfer_wrapper,
    .cs_low   = spi_cs_low_wrapper,
    .cs_high  = spi_cs_high_wrapper
};

const HAL_SPI_Driver_t* hal_spi_get_drv(void)
{
    return &spi_driver;
}
