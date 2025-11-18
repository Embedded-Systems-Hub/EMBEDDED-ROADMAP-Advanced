#include "hal_temp_sensor.h"
#include "hal_i2c.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct { void *i2c_ctx; uint8_t addr; } HAL_TempSensor_Device_t;

static int temp_init_wrapper(void *dev)
{
    HAL_TempSensor_Device_t *d = dev;

#ifdef TARGET_HOST
    printf("[TEMP_CFG] init dev=%p i2c_ctx=%p addr=0x%02X\n",
           d, d->i2c_ctx, d->addr);
#endif

    return hal_i2c_init(d->i2c_ctx);
}

static uint16_t temp_read_wrapper(void *dev)
{
    HAL_TempSensor_Device_t *d = dev;
    uint8_t raw[2];

    hal_i2c_read(d->i2c_ctx, d->addr, raw, 2);

#ifdef TARGET_HOST
    float temp = 18.0f + (rand() % 1800) / 100.0f;
    uint16_t raw12  = (uint16_t)(temp / 0.0625f);
    uint16_t packed = raw12 << 4;
    raw[0] = packed >> 8;
    raw[1] = packed & 0xFF;

    printf("[TEMP_CFG] read dev=%p i2c_ctx=%p addr=0x%02X temp=%.2fC raw12=%u packed=0x%04X\n",
           d, d->i2c_ctx, d->addr, temp, raw12, packed);
#endif

    return ((uint16_t)raw[0] << 8) | raw[1];
}

static const HAL_TempSensor_Driver_t temp_driver =
{
    .init     = temp_init_wrapper,
    .read_raw = temp_read_wrapper
};

const HAL_TempSensor_Driver_t* hal_temp_get_drv(void)
{
    return &temp_driver;
}