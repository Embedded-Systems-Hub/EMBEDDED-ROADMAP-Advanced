#ifndef HAL_ADC_H
#define HAL_ADC_H

#include <stdint.h>

typedef struct
{
    int      (*init)(void *ctx, uint8_t channel);
    uint16_t (*read_raw)(void *ctx, uint8_t channel);
} HAL_Adc_Driver_t;

int hal_adc_init(void *ctx, uint8_t channel);
uint16_t hal_adc_read_raw(void *ctx, uint8_t channel);

const HAL_Adc_Driver_t* hal_adc_get_drv(void);

#endif
