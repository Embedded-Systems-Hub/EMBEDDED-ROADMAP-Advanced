#include "light_controller.h"
#include "sensors.h"
#include "actuators.h"
#include "logger.h"

#include <stdio.h>

static const char *sensor_light  = "light_percent";
static const char *actuator_light = "light";

static float threshold_dark   = 30.0f;
static float threshold_bright = 50.0f;

static int light_state = 0;

void light_controller_update(void)
{
    float lux = sensors_read(sensor_light);

    char buf_display[64];
    snprintf(buf_display, sizeof(buf_display),
             "Light: %.1f %%\n", lux);
    logger_log(buf_display);

    int new_state = light_state;

    if (!light_state && lux < threshold_dark)
        new_state = 1;
    else if (light_state && lux > threshold_bright)
        new_state = 0;

    if (new_state != light_state)
    {
        light_state = new_state;
        actuators_write(actuator_light, &light_state);
    }

    char buf_flash[128];
    snprintf(buf_flash, sizeof(buf_flash),
             "[LIGHT] LUX=%.1f | STATE=%s\n",
             lux,
             light_state ? "ON" : "OFF");
    
    logger_log_to("flash", buf_flash);
}
