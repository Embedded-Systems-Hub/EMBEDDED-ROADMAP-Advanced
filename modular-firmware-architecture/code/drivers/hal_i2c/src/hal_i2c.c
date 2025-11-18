#include "hal_i2c.h"
#include <stdio.h>

static const HAL_I2C_Driver_t *s_drv = NULL;

int hal_i2c_init(void *ctx)
{
    s_drv = hal_i2c_get_drv();
    return s_drv && s_drv->init ? s_drv->init(ctx) : -1;
}

int hal_i2c_write(void *ctx, uint8_t addr, const uint8_t *data, size_t len)
{
    return s_drv && s_drv->write ? s_drv->write(ctx, addr, data, len) : -1;
}

int hal_i2c_read(void *ctx, uint8_t addr, uint8_t *data, size_t len)
{
    return s_drv && s_drv->read ? s_drv->read(ctx, addr, data, len) : -1;
}
