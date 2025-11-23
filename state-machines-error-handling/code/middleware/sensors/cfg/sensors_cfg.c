#include "sensors.h"
#include "interfaces.h"

#include "hal_temp_sensor.h"
#include "hal_ldr.h"

#include <stdio.h>

/*
 * Context structures for each sensor.
 * These hold HAL-related configuration (I2C address, ADC channel, etc.).
 */
typedef struct { const void *i2c_ctx; uint8_t addr;    } TempSensor_Device_t;
typedef struct { const void *adc_ctx; uint8_t channel; } LdrSensor_Device_t;

static TempSensor_Device_t temp_dev;
static LdrSensor_Device_t  ldr_dev;

/*
 * Temperature sensor initialization.
 * Binds the sensor to an I2C interface.
 */
static status_t temp_init_wrapper(void)
{
    temp_dev.i2c_ctx = interfaces_get("i2c1");
    temp_dev.addr    = 0x48U;

    return hal_temp_sensor_init(&temp_dev);
}

/*
 * Temperature sensor read.
 * Transforms raw 12-bit output into Celsius using 0.0625°C per LSB.
 */
static status_t temp_read_wrapper(float *out_value)
{
    status_t ret = STATUS_OK;
    uint16_t raw = 0U;

    CHECK_NULL(out_value);

    CHECK_STATUS(hal_temp_sensor_read(&temp_dev, &raw));

    uint16_t raw12 = raw >> 4;
    *out_value = (float)raw12 * 0.0625f;

    return ret;
}

/*
 * LDR initialization.
 * Associates the sensor with an ADC channel.
 */
static status_t ldr_init_wrapper(void)
{
    ldr_dev.adc_ctx  = interfaces_get("adc1");
    ldr_dev.channel  = 1U;

    return hal_ldr_init(&ldr_dev);
}

/*
 * LDR read.
 * Converts raw ADC (0–4095) to percentage (0–100%).
 */
static status_t ldr_read_wrapper(float *out_value)
{
    status_t ret = STATUS_OK;
    uint16_t raw = 0U;

    CHECK_NULL(out_value);

    CHECK_STATUS(hal_ldr_read(&ldr_dev, &raw));

    *out_value = (raw * 100.0f) / 4095.0f;

    return ret;
}

/*
 * Static sensor table exposed to the middleware.
 */
static const SensorDesc_t sensor_table[] =
{
    { "temperature_celsius", temp_init_wrapper, temp_read_wrapper },
    { "light_percent",       ldr_init_wrapper,  ldr_read_wrapper  },
};

const SensorDesc_t* sensors_get_table(size_t *count)
{
    *count = sizeof(sensor_table) / sizeof(sensor_table[0]);
    return sensor_table;
}
