#ifndef HAL_DISPLAY_H
#define HAL_DISPLAY_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "error_codes.h"

typedef struct
{
    status_t (*init)(void *dev);
    status_t (*write)(void *dev, const uint8_t *data, size_t len);
} HAL_Display_Driver_t;

status_t hal_display_init(void *dev);
status_t hal_display_write(void *dev, const uint8_t *data, size_t len);

const HAL_Display_Driver_t* hal_display_get_drv(void);

#endif
