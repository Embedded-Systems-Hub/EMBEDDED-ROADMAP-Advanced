#ifndef HAL_ADC_H
#define HAL_ADC_H

#include <stdio.h>
#include <stdint.h>
#include "error_codes.h"

typedef struct
{
	status_t (*init)(void *ctx, uint8_t channel);
    status_t (*read)(void *ctx, void *out);
} HAL_Adc_Driver_t;

status_t hal_adc_init(void *ctx, uint8_t channel);
status_t hal_adc_read(void *ctx, void *out);

const HAL_Adc_Driver_t* hal_adc_get_drv(void);

#endif
