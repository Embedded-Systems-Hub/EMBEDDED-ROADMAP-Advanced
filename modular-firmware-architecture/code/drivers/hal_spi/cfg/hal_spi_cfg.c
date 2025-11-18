#include "hal_spi.h"
#include <stdio.h>

static int spi_init_wrapper(void *ctx)
{
#ifdef TARGET_HOST
    printf("[SPI_CFG] init ctx=%p\n", ctx);
#endif
    return 0;
}

static int spi_write_wrapper(void *ctx, const uint8_t *data, size_t len)
{
#ifdef TARGET_HOST
    printf("[SPI_CFG] write ctx=%p len=%zu data=[ ", ctx, len);
    for (size_t i = 0; i < len; i++)
        printf("%02X ", data[i]);
    printf("]\n");
#endif
    return (int)len;
}

static int spi_read_wrapper(void *ctx, uint8_t *data, size_t len)
{
#ifdef TARGET_HOST
    printf("[SPI_CFG] read ctx=%p len=%zu -> zeros\n", ctx, len);
#endif

    for (size_t i = 0; i < len; i++)
        data[i] = 0;

    return (int)len;
}

static int spi_transfer_wrapper(void *ctx, const uint8_t *tx, uint8_t *rx, size_t len)
{
#ifdef TARGET_HOST
    printf("[SPI_CFG] transfer ctx=%p len=%zu tx=[ ", ctx, len);
    for (size_t i = 0; i < len; i++)
        printf("%02X ", tx[i]);
    printf("]\n");
#endif

    for (size_t i = 0; i < len; i++)
        rx[i] = 0;

    return (int)len;
}

static int spi_cs_low_wrapper(void *ctx, uint8_t cs_pin)
{
#ifdef TARGET_HOST
    printf("[SPI_CFG] CS LOW ctx=%p pin=%u\n", ctx, cs_pin);
#endif
    return 0;
}

static int spi_cs_high_wrapper(void *ctx, uint8_t cs_pin)
{
#ifdef TARGET_HOST
    printf("[SPI_CFG] CS HIGH ctx=%p pin=%u\n", ctx, cs_pin);
#endif
    return 0;
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
