#include "hal_led.h"
#include "error_codes.h"

static const HAL_LED_Driver_t *s_drv = NULL;

status_t hal_led_init(void *dev)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(dev);

    s_drv = hal_led_get_drv();
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->init);

    CHECK_STATUS(s_drv->init(dev));

    return ret;
}

status_t hal_led_write(void *dev, uint8_t on)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(dev);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->set_state);

    CHECK_STATUS(s_drv->set_state(dev, on));

    return ret;
}
