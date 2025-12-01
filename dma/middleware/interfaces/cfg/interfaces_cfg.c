#include <stdio.h>
#include "interfaces.h"
#include "stm32f4xx_hal.h"

static ADC_HandleTypeDef adc_pot_ctx;
DMA_HandleTypeDef hdma_adc1;
static TIM_HandleTypeDef pwm_led_ctx;
DMA_HandleTypeDef hdma_tim4_ch1;

static volatile uint16_t dma_buffer;

static InterfaceEntry_t iface_table[] =
{
    { "adc_pot", &adc_pot_ctx, (void*)&dma_buffer },
    { "pwm_led", &pwm_led_ctx, (void*)&dma_buffer }
};

const InterfaceEntry_t* interfaces_get_table(size_t *count)
{
    *count = sizeof(iface_table) / sizeof(iface_table[0]);
    return iface_table;
}
