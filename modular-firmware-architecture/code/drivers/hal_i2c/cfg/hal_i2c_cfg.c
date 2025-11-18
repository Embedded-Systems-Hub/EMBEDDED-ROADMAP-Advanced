#include "hal_i2c.h"
#include <stdio.h>

static int i2c_init_wrapper(void *ctx)
{
#ifdef TARGET_HOST
    printf("[I2C_CFG] init ctx=%p\n", ctx);
#endif
    return 0;
}

static int i2c_write_wrapper(void *ctx, uint8_t addr, const uint8_t *data, size_t len)
{
#ifdef TARGET_HOST
    printf("[I2C_CFG] write ctx=%p addr=0x%02X len=%zu data=[ ", ctx, addr, len);
    for (size_t i = 0; i < len; i++)
        printf("%02X ", data[i]);
    printf("]\n");
#endif
    return (int)len;
}

static int i2c_read_wrapper(void *ctx, uint8_t addr, uint8_t *data, size_t len)
{
#ifdef TARGET_HOST
    printf("[I2C_CFG] read ctx=%p addr=0x%02X len=%zu -> zeros\n",
           ctx, addr, len);
#endif

    for (size_t i = 0; i < len; i++)
        data[i] = 0;

    return (int)len;
}

static const HAL_I2C_Driver_t i2c_driver =
{
    .init  = i2c_init_wrapper,
    .write = i2c_write_wrapper,
    .read  = i2c_read_wrapper
};

const HAL_I2C_Driver_t* hal_i2c_get_drv(void)
{
    return &i2c_driver;
}
