#ifndef HAL_DISPLAY_H
#define HAL_DISPLAY_H

#include <stdint.h>
#include <stddef.h>

typedef struct
{
    int (*init)(void *dev);
    int (*write)(void *dev, const uint8_t *data, size_t len);

} HAL_Display_Driver_t;

int hal_display_init(void *dev);
int hal_display_write(void *dev, const uint8_t *data, size_t len);

const HAL_Display_Driver_t* hal_display_get_drv(void);

#endif
