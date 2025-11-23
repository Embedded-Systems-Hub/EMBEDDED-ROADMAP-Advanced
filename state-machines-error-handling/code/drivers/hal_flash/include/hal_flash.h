#ifndef HAL_FLASH_H
#define HAL_FLASH_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "error_codes.h"

typedef struct
{
    status_t (*init)(void *dev);
    status_t (*read)(void *dev, uint32_t addr, uint8_t *data, size_t len);
    status_t (*write)(void *dev, uint32_t addr, const uint8_t *data, size_t len);
} HAL_Flash_Driver_t;

status_t hal_flash_init(void *dev);
status_t hal_flash_read(void *dev, uint32_t addr, uint8_t *data, size_t len);
status_t hal_flash_write(void *dev, uint32_t addr, const uint8_t *data, size_t len);

const HAL_Flash_Driver_t* hal_flash_get_drv(void);

#endif
