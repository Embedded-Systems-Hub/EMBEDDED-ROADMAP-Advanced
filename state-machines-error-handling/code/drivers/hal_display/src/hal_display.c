#include "hal_display.h"
#include "error_codes.h"

static const HAL_Display_Driver_t *s_drv = NULL;

status_t hal_display_init(void *dev)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(dev);

    s_drv = hal_display_get_drv();
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->init);

    CHECK_STATUS(s_drv->init(dev));

    return ret;
}

status_t hal_display_write(void *dev, const uint8_t *data, size_t len)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(dev);
    CHECK_NULL(data);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->write);

    CHECK_STATUS(s_drv->write(dev, data, len));

    return ret;
}
