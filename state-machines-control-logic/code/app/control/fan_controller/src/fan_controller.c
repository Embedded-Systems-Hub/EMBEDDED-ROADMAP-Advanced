#include "fan_controller.h"
#include "sensors.h"
#include "actuators.h"
#include "logger.h"

#include <stdio.h>

static const char *sensor_temp = "temperature_celsius";
static const char *actuator_fan = "ventilation";

static float threshold_on_low   = 30.0f;
static float threshold_on_high  = 40.0f;
static float threshold_to_low   = 35.0f;
static float threshold_off      = 25.0f;

static fan_state_t fan_state = FAN_OFF;

void fan_controller_update(void)
{
    float temp = sensors_read(sensor_temp);

    char buf_display[64];
    snprintf(buf_display, sizeof(buf_display),
             "Temperature: %.2f C\n", temp);
    logger_log(buf_display);

    fan_state_t new_state = fan_state;

    switch (fan_state)
    {
        case FAN_OFF:
            if (temp > threshold_on_low)
                new_state = FAN_LOW;
            break;

        case FAN_LOW:
            if (temp > threshold_on_high)
                new_state = FAN_HIGH;
            else if (temp < threshold_off)
                new_state = FAN_OFF;
            break;

        case FAN_HIGH:
            if (temp < threshold_to_low)
                new_state = FAN_LOW;
            break;

        case FAN_ERROR:
            break;
    }

    if (new_state != fan_state)
    {
        fan_state = new_state;
        actuators_write(actuator_fan, &fan_state);
    }

    char buf_flash[128];
    snprintf(buf_flash, sizeof(buf_flash),
             "[FAN] TEMP=%.2f | STATE=%d\n",
             temp,
             fan_state);

    logger_log_to("flash", buf_flash);
}
