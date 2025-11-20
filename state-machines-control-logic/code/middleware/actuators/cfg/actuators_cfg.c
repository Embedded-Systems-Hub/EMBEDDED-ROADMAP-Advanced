#include "actuators.h"
#include "interfaces.h"

#include "hal_fan.h"
#include "hal_led.h"
#include "hal_display.h"

#include <stdbool.h>
#include <string.h>

typedef struct { const void *gpio_ctx; uint8_t pin; } Fan_Device_t;
typedef struct { const void *gpio_ctx; uint8_t pin; } Led_Device_t;
typedef struct { const void *uart_ctx; }              Display_Device_t;

static Fan_Device_t     fan_dev;
static Led_Device_t     led_dev;
static Display_Device_t display_dev;

static void fan_init_wrapper(void)
{
    fan_dev.gpio_ctx = interfaces_get("gpioA");
    fan_dev.pin  = 6;
    hal_fan_init(&fan_dev);
}

static void fan_write_wrapper(const void *data)
{
    int state = *(const int*)data;

    uint8_t speed = 0;

    if (state <= 0)
        speed = 0; // OFF
    else if (state == 1)
        speed = 1; // LOW
    else if (state == 2)
        speed = 2; // HIGH
    else
        speed = 0;

    hal_fan_write(&fan_dev, speed);
}

static void light_init_wrapper(void)
{
    led_dev.gpio_ctx = interfaces_get("gpioA");
    led_dev.pin  = 2;
    hal_led_init(&led_dev);
}

static void light_write_wrapper(const void *data)
{
    bool on = *(const bool*)data;
    hal_led_write(&led_dev, on);
}

static void display_init_wrapper(void)
{
    display_dev.uart_ctx = interfaces_get("uart1");
    hal_display_init(&display_dev);
}

static void display_write_wrapper(const void *data)
{
    const char *msg = data;
    hal_display_write(&display_dev, (const uint8_t*)msg, strlen(msg));
}

static ActuatorDesc_t table[] =
{
    { "ventilation", fan_init_wrapper,    fan_write_wrapper    },
    { "light",       light_init_wrapper,  light_write_wrapper  },
    { "display",     display_init_wrapper, display_write_wrapper }
};

const ActuatorDesc_t* actuators_get_table(size_t *count)
{
    *count = sizeof(table)/sizeof(table[0]);
    return table;
}
