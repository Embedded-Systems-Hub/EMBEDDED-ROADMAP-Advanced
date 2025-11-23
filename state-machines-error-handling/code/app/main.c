#include <stdio.h>
#include <unistd.h>

#include "error_codes.h"

/* App */
#include "fan_controller.h"
#include "light_controller.h"

/* Middleware */
#include "interfaces.h"
#include "sensors.h"
#include "actuators.h"
#include "storage.h"
#include "logger.h"

typedef enum {
    SYS_STATE_INIT = 0,
    SYS_STATE_RUNNING,
    SYS_STATE_ERROR,
    SYS_STATE_RECOVERY
} system_state_t;

static system_state_t sys_state = SYS_STATE_INIT;
static status_t last_error = STATUS_OK;

static status_t system_init(void)
{
    interfaces_init();

    CHECK_STATUS(sensors_init());
    CHECK_STATUS(actuators_init());
    CHECK_STATUS(storage_init());

    logger_init();
    logger_log(LOG_INFO, "System init OK\r\n");

    return STATUS_OK;
}

static status_t system_run_cycle(void)
{
    CHECK_STATUS(fan_controller_update());
    CHECK_STATUS(light_controller_update());

    return STATUS_OK;
}

static status_t system_attempt_recovery(void)
{

    return sensors_init();
}

int main(void)
{
    while (1)
    {
        switch (sys_state)
        {
        case SYS_STATE_INIT:
            last_error = system_init();
            if (last_error == STATUS_OK)
                sys_state = SYS_STATE_RUNNING;
            else
                sys_state = SYS_STATE_ERROR;
            break;

        case SYS_STATE_RUNNING:
            printf("\n-- New loop --\r\n");
            last_error = system_run_cycle();
            if (last_error != STATUS_OK)
                sys_state = SYS_STATE_ERROR;
            sleep(1);
            break;

        case SYS_STATE_ERROR:
            // TODO: error state logic
            logger_log(LOG_ERROR, "System error: %d\r\n", last_error);
            sys_state = SYS_STATE_RECOVERY;
            break;

        case SYS_STATE_RECOVERY:
            // TODO: recovery state logic
            logger_log(LOG_WARN, "Attempting system recovery...\r\n");
            sys_state = SYS_STATE_INIT;
            break;
        }
    }

    return 0;
}
