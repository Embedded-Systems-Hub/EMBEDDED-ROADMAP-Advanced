#include "hal_led.h"
#include <stdio.h>

static const HAL_LED_Driver_t *s_drv = NULL;

status_t hal_led_init(void *dev)
{
    CHECK_NULL(dev);

    s_drv = hal_led_get_drv();
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->init);

    CHECK_STATUS(s_drv->init(dev));

    return STATUS_OK;
}

status_t hal_led_write(void *dev, const void *in)
{
    CHECK_NULL(dev);
    CHECK_NULL(in);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->set);

    CHECK_STATUS(s_drv->set(dev, in));

    return STATUS_OK;
}
