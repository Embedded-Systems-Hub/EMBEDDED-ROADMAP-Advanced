#include "actuators.h"
#include "interfaces.h"

#include "hal_fan.h"
#include "hal_led.h"
#include "hal_display.h"

#include <stdbool.h>
#include <string.h>
#include "error_codes.h"

typedef struct { const void *pwm_ctx;  uint8_t channel; } Fan_Device_t;
typedef struct { const void *gpio_ctx; uint8_t pin;     } Led_Device_t;
typedef struct { const void *uart_ctx;                 } Display_Device_t;

static Fan_Device_t     fan_dev;
static Led_Device_t     led_dev;
static Display_Device_t display_dev;

static status_t fan_init_wrapper(void)
{
    status_t ret = STATUS_OK;

    fan_dev.pwm_ctx = interfaces_get("pwm1");
    fan_dev.channel = 0U;

    ret = hal_fan_init(&fan_dev);

    return ret;
}

static status_t fan_write_wrapper(const void *data)
{
    status_t ret = STATUS_OK;
    uint8_t speed = 0U;

    CHECK_NULL(data);

    int state = *(const int*)data;

    if (state <= 0)
        speed = 0U;
    else if (state == 1)
        speed = 1U;
    else if (state == 2)
        speed = 2U;
    else
        ret = STATUS_ERR_INVALID_PARAM;

    if (ret == STATUS_OK)
        ret = hal_fan_write(&fan_dev, speed);

    return ret;
}

static status_t light_init_wrapper(void)
{
    status_t ret = STATUS_OK;

    led_dev.gpio_ctx = interfaces_get("gpioA");
    led_dev.pin      = 2U;

    ret = hal_led_init(&led_dev);

    return ret;
}

static status_t light_write_wrapper(const void *data)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(data);

    bool on = *(const bool*)data;
    ret = hal_led_write(&led_dev, on);

    return ret;
}

static status_t display_init_wrapper(void)
{
    status_t ret = STATUS_OK;

    display_dev.uart_ctx = interfaces_get("uart1");
    ret = hal_display_init(&display_dev);

    return ret;
}

static status_t display_write_wrapper(const void *data)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(data);

    const char *msg = (const char*)data;

    ret = hal_display_write(
        &display_dev,
        (const uint8_t*)msg,
        strlen(msg)
    );

    return ret;
}

static const ActuatorDesc_t table[] =
{
    { "ventilation", fan_init_wrapper,     fan_write_wrapper     },
    { "light",       light_init_wrapper,   light_write_wrapper   },
    { "display",     display_init_wrapper, display_write_wrapper }
};

const ActuatorDesc_t* actuators_get_table(size_t *count)
{
    *count = sizeof(table) / sizeof(table[0]);
    return table;
}
