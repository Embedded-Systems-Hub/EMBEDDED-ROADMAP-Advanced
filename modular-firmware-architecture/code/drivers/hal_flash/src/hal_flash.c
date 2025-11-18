#include "hal_flash.h"
#include <stdio.h>

static const HAL_Flash_Driver_t *s_drv = NULL;

int hal_flash_init(void *dev)
{
    s_drv = hal_flash_get_drv();
    return s_drv && s_drv->init ? s_drv->init(dev) : -1;
}

int hal_flash_read(void *dev, uint32_t addr, uint8_t *data, size_t len)
{
    return s_drv && s_drv->read ? s_drv->read(dev, addr, data, len) : -1;
}

int hal_flash_write(void *dev, uint32_t addr, const uint8_t *data, size_t len)
{
    return s_drv && s_drv->write ? s_drv->write(dev, addr, data, len) : -1;
}
