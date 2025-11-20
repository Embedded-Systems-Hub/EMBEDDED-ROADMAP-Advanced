#ifndef HAL_FLASH_H
#define HAL_FLASH_H

#include <stdint.h>
#include <stddef.h>

typedef struct
{
    int (*init)(void *dev);
    int (*read)(void *dev, uint32_t addr, uint8_t *data, size_t len);
    int (*write)(void *dev, uint32_t addr, const uint8_t *data, size_t len);

} HAL_Flash_Driver_t;

int  hal_flash_init(void *dev);
int  hal_flash_read(void *dev, uint32_t addr, uint8_t *data, size_t len);
int  hal_flash_write(void *dev, uint32_t addr, const uint8_t *data, size_t len);

const HAL_Flash_Driver_t* hal_flash_get_drv(void);

#endif
