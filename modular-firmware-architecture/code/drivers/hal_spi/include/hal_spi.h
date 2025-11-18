#ifndef HAL_SPI_H
#define HAL_SPI_H

#include <stdint.h>
#include <stddef.h>

typedef struct
{
    int (*init)(void *ctx);
    int (*write)(void *ctx, const uint8_t *data, size_t len);
    int (*read)(void *ctx, uint8_t *data, size_t len);
    int (*transfer)(void *ctx, const uint8_t *tx, uint8_t *rx, size_t len);
    int (*cs_low)(void *ctx, uint8_t cs_pin);
    int (*cs_high)(void *ctx, uint8_t cs_pin);
} HAL_SPI_Driver_t;

int hal_spi_init(void *ctx);
int hal_spi_write(void *ctx, const uint8_t *data, size_t len);
int hal_spi_read(void *ctx, uint8_t *data, size_t len);
int hal_spi_transfer(void *ctx, const uint8_t *tx, uint8_t *rx, size_t len);
int hal_spi_cs_low(void *ctx, uint8_t cs_pin);
int hal_spi_cs_high(void *ctx, uint8_t cs_pin);

const HAL_SPI_Driver_t* hal_spi_get_drv(void);

#endif
