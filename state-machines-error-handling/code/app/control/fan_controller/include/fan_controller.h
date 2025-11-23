#ifndef FAN_CONTROLLER_H
#define FAN_CONTROLLER_H

#include "error_codes.h"

typedef enum {
    FAN_OFF = 0,
    FAN_LOW,
    FAN_HIGH,
    FAN_ERROR
} fan_state_t;

status_t fan_controller_update(void);

#endif
