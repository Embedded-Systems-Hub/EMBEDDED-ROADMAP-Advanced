#ifndef HAL_I2C_H
#define HAL_I2C_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "error_codes.h"

typedef struct
{
    status_t (*init)(void *ctx);
    status_t (*write)(void *ctx, uint8_t addr, const uint8_t *data, size_t len);
    status_t (*read)(void *ctx, uint8_t addr, uint8_t *data, size_t len);
} HAL_I2C_Driver_t;

status_t hal_i2c_init(void *ctx);
status_t hal_i2c_write(void *ctx, uint8_t addr, const uint8_t *data, size_t len);
status_t hal_i2c_read(void *ctx, uint8_t addr, uint8_t *data, size_t len);

const HAL_I2C_Driver_t* hal_i2c_get_drv(void);

#endif
