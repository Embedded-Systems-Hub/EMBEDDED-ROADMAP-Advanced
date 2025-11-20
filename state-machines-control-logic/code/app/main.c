#include <stdio.h>
#include <unistd.h>

/* App */
#include "fan_controller.h"
#include "light_controller.h"

/* Middleware */
#include "interfaces.h"
#include "sensors.h"
#include "actuators.h"
#include "storage.h"
#include "logger.h"

int main(void)
{
    /* Middleware */
    interfaces_init();
    sensors_init();
    actuators_init();
    storage_init();
    logger_init();
    logger_log("System boot OK\n");

    while (1)
    {
        printf("\n-- New loop --\r\n");
        fan_controller_update();
        light_controller_update();

        sleep(1);
    }

    return 0;
}
