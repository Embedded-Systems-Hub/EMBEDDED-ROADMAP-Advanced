#include "light_controller.h"
#include "sensors.h"
#include "actuators.h"
#include "logger.h"
#include "error_codes.h"

#include <stdio.h>

static const char *sensor_light   = "light_percent";
static const char *actuator_light = "light";

static const float LIGHT_THRESHOLD_DARK   = 30.0f;
static const float LIGHT_THRESHOLD_BRIGHT = 50.0f;

static light_state_t light_state = LIGHT_OFF;
static float last_valid_lux = 50.0f;

status_t light_controller_update(void)
{
    status_t ret = STATUS_OK;
    float lux = 0.0f;
    light_state_t new_state = light_state;

    ret = sensors_read(sensor_light, &lux);
    if (ret != STATUS_OK)
    {
        lux = last_valid_lux;
        logger_log(LOG_WARN, "[LIGHT] Sensor read failed, using fallback\n");
    }
    else
    {
        last_valid_lux = lux;
    }

    char buf_display[64];
    (void)snprintf(buf_display, sizeof(buf_display),
                   "Light: %.1f %%\n", lux);
    logger_log(LOG_INFO, buf_display);

    if ((light_state == LIGHT_OFF) && (lux < LIGHT_THRESHOLD_DARK))
        new_state = LIGHT_ON;
    else if ((light_state == LIGHT_ON) && (lux > LIGHT_THRESHOLD_BRIGHT))
        new_state = LIGHT_OFF;

    if (new_state != light_state)
    {
        light_state = new_state;

        status_t act_ret = actuators_write(actuator_light, &light_state);
        if (act_ret != STATUS_OK)
        {
            logger_log(LOG_ERROR, "[LIGHT] Actuator write failed\n");
            ret = act_ret;
        }
    }

    char buf_flash[128];
    (void)snprintf(buf_flash, sizeof(buf_flash),
                   "[LIGHT] LUX=%.1f | STATE=%s\n",
                   lux,
                   (light_state == LIGHT_ON) ? "ON" : "OFF");

    logger_log_to("flash", LOG_INFO, buf_flash);

    return ret;
}
