#ifndef HAL_I2C_H
#define HAL_I2C_H

#include <stdint.h>
#include <stddef.h>

typedef struct
{
    int (*init)(void *ctx);
    int (*write)(void *ctx, uint8_t addr, const uint8_t *data, size_t len);
    int (*read)(void *ctx, uint8_t addr, uint8_t *data, size_t len);

} HAL_I2C_Driver_t;

int hal_i2c_init(void *ctx);
int hal_i2c_write(void *ctx, uint8_t addr, const uint8_t *data, size_t len);
int hal_i2c_read(void *ctx, uint8_t addr, uint8_t *data, size_t len);

const HAL_I2C_Driver_t* hal_i2c_get_drv(void);

#endif
