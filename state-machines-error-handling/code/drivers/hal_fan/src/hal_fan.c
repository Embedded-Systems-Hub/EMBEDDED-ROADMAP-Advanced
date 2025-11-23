#include "hal_fan.h"
#include "error_codes.h"

static const HAL_Fan_Driver_t *s_drv = NULL;

status_t hal_fan_init(void *dev)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(dev);

    s_drv = hal_fan_get_drv();
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->init);

    CHECK_STATUS(s_drv->init(dev));

    return ret;
}

status_t hal_fan_write(void *dev, uint8_t val)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(dev);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->set_state);

    CHECK_STATUS(s_drv->set_state(dev, val));

    return ret;
}
