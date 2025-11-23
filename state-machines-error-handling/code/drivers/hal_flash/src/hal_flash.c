#include "hal_flash.h"
#include "error_codes.h"

static const HAL_Flash_Driver_t *s_drv = NULL;

status_t hal_flash_init(void *dev)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(dev);

    s_drv = hal_flash_get_drv();
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->init);

    CHECK_STATUS(s_drv->init(dev));

    return ret;
}

status_t hal_flash_read(void *dev, uint32_t addr, uint8_t *data, size_t len)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(dev);
    CHECK_NULL(data);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->read);

    CHECK_STATUS(s_drv->read(dev, addr, data, len));

    return ret;
}

status_t hal_flash_write(void *dev, uint32_t addr, const uint8_t *data, size_t len)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(dev);
    CHECK_NULL(data);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->write);

    CHECK_STATUS(s_drv->write(dev, addr, data, len));

    return ret;
}
