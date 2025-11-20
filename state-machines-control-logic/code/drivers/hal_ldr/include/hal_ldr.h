#ifndef HAL_LDR_H
#define HAL_LDR_H

#include <stdint.h>

typedef struct
{
    int      (*init)(void *dev);
    uint16_t (*read_raw)(void *dev);

} HAL_Ldr_Driver_t;

int      hal_ldr_init(void *dev);
uint16_t hal_ldr_read(void *dev);

const HAL_Ldr_Driver_t* hal_ldr_get_drv(void);

#endif
