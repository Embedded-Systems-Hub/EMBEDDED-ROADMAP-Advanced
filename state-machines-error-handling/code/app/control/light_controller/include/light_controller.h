#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#include "error_codes.h"

/* Light state. */
typedef enum
{
    LIGHT_OFF = 0,
    LIGHT_ON  = 1,
    LIGHT_MAX
} light_state_t;

/* Updates the light control logic (hysteresis). */
status_t light_controller_update(void);

#endif /* LIGHT_CONTROLLER_H */
