#ifndef HAL_LDR_H
#define HAL_LDR_H

#include <stdio.h>
#include <stdint.h>
#include "error_codes.h"

typedef struct
{
    status_t (*init)(void *dev);
    status_t (*read_raw)(void *dev, uint16_t *out_raw);
} HAL_Ldr_Driver_t;

status_t hal_ldr_init(void *dev);
status_t hal_ldr_read(void *dev, uint16_t *out_raw);

const HAL_Ldr_Driver_t* hal_ldr_get_drv(void);

#endif
