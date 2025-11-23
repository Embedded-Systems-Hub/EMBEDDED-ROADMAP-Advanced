#include "hal_ldr.h"
#include "error_codes.h"

static const HAL_Ldr_Driver_t *s_drv = NULL;

status_t hal_ldr_init(void *dev)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(dev);

    s_drv = hal_ldr_get_drv();
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->init);

    CHECK_STATUS(s_drv->init(dev));

    return ret;
}

status_t hal_ldr_read(void *dev, uint16_t *out_raw)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(dev);
    CHECK_NULL(out_raw);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->read_raw);

    CHECK_STATUS(s_drv->read_raw(dev, out_raw));

    return ret;
}
