#include <stdio.h>
#include "hal_potentiometer.h"

static const HAL_Potentiometer_Driver_t *s_drv = NULL;

status_t hal_potentiometer_init(void *dev)
{
    CHECK_NULL(dev);

    s_drv = hal_potentiometer_get_drv();
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->init);

    CHECK_STATUS(s_drv->init(dev));

    return STATUS_OK;
}

status_t hal_potentiometer_read(void *dev, void *out)
{
    CHECK_NULL(dev);
    CHECK_NULL(out);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->read);

    CHECK_STATUS(s_drv->read(dev, out));

    return STATUS_OK;
}
