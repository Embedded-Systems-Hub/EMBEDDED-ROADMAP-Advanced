#ifndef HAL_SPI_H
#define HAL_SPI_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "error_codes.h"

typedef struct
{
    status_t (*init)(void *ctx);
    status_t (*write)(void *ctx, const uint8_t *data, size_t len);
    status_t (*read)(void *ctx, uint8_t *data, size_t len);
    status_t (*transfer)(void *ctx, const uint8_t *tx, uint8_t *rx, size_t len);
    status_t (*cs_low)(void *ctx, uint8_t cs_pin);
    status_t (*cs_high)(void *ctx, uint8_t cs_pin);
} HAL_SPI_Driver_t;

status_t hal_spi_init(void *ctx);
status_t hal_spi_write(void *ctx, const uint8_t *data, size_t len);
status_t hal_spi_read(void *ctx, uint8_t *data, size_t len);
status_t hal_spi_transfer(void *ctx, const uint8_t *tx, uint8_t *rx, size_t len);
status_t hal_spi_cs_low(void *ctx, uint8_t cs_pin);
status_t hal_spi_cs_high(void *ctx, uint8_t cs_pin);

const HAL_SPI_Driver_t* hal_spi_get_drv(void);

#endif
