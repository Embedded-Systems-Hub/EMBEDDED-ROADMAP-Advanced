#include "hal_flash.h"
#include "hal_spi.h"
#include "error_codes.h"

typedef struct { void *spi_ctx; uint8_t cs_pin; } HAL_Flash_Device_t;

static status_t flash_init_wrapper(void *dev)
{
    status_t ret = STATUS_OK;
    HAL_Flash_Device_t *d = dev;

    CHECK_NULL(d);
    CHECK_NULL(d->spi_ctx);

#ifdef TARGET_HOST
    printf("[FLASH_CFG] init dev=%p spi_ctx=%p cs=%u\n",
           d, d->spi_ctx, d->cs_pin);
#endif

    CHECK_STATUS(hal_spi_init(d->spi_ctx));

    return ret;
}

static status_t flash_read_wrapper(void *dev, uint32_t addr, uint8_t *data, size_t len)
{
    status_t ret = STATUS_OK;
    HAL_Flash_Device_t *d = dev;

    CHECK_NULL(d);
    CHECK_NULL(d->spi_ctx);
    CHECK_NULL(data);

#ifdef TARGET_HOST
    printf("[FLASH_CFG] read dev=%p spi_ctx=%p cs=%u addr=0x%06X len=%zu\n",
           d, d->spi_ctx, d->cs_pin, addr, len);
#endif

    uint8_t cmd[4] =
    {
        0x03,
        (addr >> 16) & 0xFF,
        (addr >> 8)  & 0xFF,
        addr & 0xFF
    };

    CHECK_STATUS(hal_spi_cs_low(d->spi_ctx, d->cs_pin));
    CHECK_STATUS(hal_spi_write(d->spi_ctx, cmd, sizeof(cmd)));
    CHECK_STATUS(hal_spi_read(d->spi_ctx, data, len));
    CHECK_STATUS(hal_spi_cs_high(d->spi_ctx, d->cs_pin));

    return ret;
}

static status_t flash_write_wrapper(void *dev, uint32_t addr, const uint8_t *data, size_t len)
{
    status_t ret = STATUS_OK;
    HAL_Flash_Device_t *d = dev;

    CHECK_NULL(d);
    CHECK_NULL(d->spi_ctx);
    CHECK_NULL(data);

#ifdef TARGET_HOST
    printf("[FLASH_CFG] write dev=%p spi_ctx=%p cs=%u addr=0x%06X len=%zu\n",
           d, d->spi_ctx, d->cs_pin, addr, len);
#endif

    uint8_t cmd[4] =
    {
        0x02,
        (addr >> 16) & 0xFF,
        (addr >> 8)  & 0xFF,
        addr & 0xFF
    };

    CHECK_STATUS(hal_spi_cs_low(d->spi_ctx, d->cs_pin));
    CHECK_STATUS(hal_spi_write(d->spi_ctx, cmd, sizeof(cmd)));
    CHECK_STATUS(hal_spi_write(d->spi_ctx, data, len));
    CHECK_STATUS(hal_spi_cs_high(d->spi_ctx, d->cs_pin));

    return ret;
}

static const HAL_Flash_Driver_t flash_driver =
{
    .init  = flash_init_wrapper,
    .read  = flash_read_wrapper,
    .write = flash_write_wrapper
};

const HAL_Flash_Driver_t* hal_flash_get_drv(void)
{
    return &flash_driver;
}
