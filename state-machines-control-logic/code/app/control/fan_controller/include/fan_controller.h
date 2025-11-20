#ifndef FAN_CONTROLLER_H
#define FAN_CONTROLLER_H

typedef enum {
    FAN_OFF = 0,
    FAN_LOW,
    FAN_HIGH,
    FAN_ERROR
} fan_state_t;

void fan_controller_update(void);

#endif
