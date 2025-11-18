#include "fan_controller.h"
#include "sensors.h"
#include "actuators.h"
#include "logger.h"

#include <stdio.h>

static const char *sensor_temp = "temperature_celsius";
static const char *actuator_fan = "ventilation";

static float threshold_on  = 30.0f;
static float threshold_off = 27.0f;

static int fan_state = 0;

void fan_controller_update(void)
{
    float temp = sensors_read(sensor_temp);

    char buf_display[64];
    snprintf(buf_display, sizeof(buf_display),
             "Temperature: %.2f C\n", temp);
    logger_log(buf_display);

    int new_state = fan_state;

    if (!fan_state && temp > threshold_on)
        new_state = 1;
    else if (fan_state && temp < threshold_off)
        new_state = 0;

    if (new_state != fan_state)
    {
        fan_state = new_state;
        actuators_write(actuator_fan, &fan_state);
    }

    char buf_flash[128];
    snprintf(buf_flash, sizeof(buf_flash),
             "[FAN] TEMP=%.2f | STATE=%s\n",
             temp,
             fan_state ? "ON" : "OFF");

    logger_log_to("flash", buf_flash);
}
