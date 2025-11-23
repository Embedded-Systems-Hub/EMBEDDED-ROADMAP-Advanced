#include "fan_controller.h"
#include "sensors.h"
#include "actuators.h"
#include "logger.h"
#include "error_codes.h"

#include <stdio.h>

static const char *sensor_temp = "temperature_celsius";
static const char *actuator_fan = "ventilation";

static const float temp_min_valid = -50.0f;
static const float temp_max_valid = 150.0f;

static const float threshold_on_low   = 30.0f;
static const float threshold_on_high  = 40.0f;
static const float threshold_to_low   = 35.0f;
static const float threshold_off      = 25.0f;

static fan_state_t fan_state       = FAN_OFF;
static float       last_valid_temp = 25.0f;

status_t fan_controller_update(void)
{
    status_t ret = STATUS_OK;
    float temp = 0.0f;
    fan_state_t new_state = fan_state;

    ret = sensors_read(sensor_temp, &temp);
    if (ret != STATUS_OK)
    {
        temp = last_valid_temp;
        (void)logger_log(LOG_WARN, "[FAN] Sensor read failed, using fallback\n");
    }
    else
    {
        if ((temp < temp_min_valid) || (temp > temp_max_valid))
        {
            temp = last_valid_temp;
            (void)logger_log(LOG_ERROR, "[FAN] Sensor out of range, fallback\n");
        }
        else
        {
            last_valid_temp = temp;
        }
    }

    (void)logger_log(LOG_INFO, "Temperature: %.2f C\n", temp);

    /* --- STATE MACHINE --- */
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
            (void)logger_log(LOG_DEBUG, "[FAN] In error state, forcing OFF\n");
            new_state = FAN_OFF;
            break;

        default:
            (void)logger_log(LOG_FATAL, "[FAN] Invalid state\n");
            return STATUS_ERR_UNKNOWN;
    }

    if (new_state != fan_state)
    {
        fan_state = new_state;

        int fan_cmd = 0;
        if (fan_state == FAN_LOW || fan_state == FAN_HIGH)
            fan_cmd = 1;

        CHECK_STATUS(actuators_write(actuator_fan, &fan_cmd));
    }

    (void)logger_log_to("flash", LOG_DEBUG,
                        "[FAN] TEMP=%.2f | STATE=%d\n",
                        temp, (int)fan_state);

    return STATUS_OK;
}
