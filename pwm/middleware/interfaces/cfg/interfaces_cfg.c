#include <stdio.h>
#include "interfaces.h"
#include "stm32f4xx_hal.h"

static ADC_HandleTypeDef adc_pot_ctx;
static TIM_HandleTypeDef pwm_led_ctx;

static InterfaceEntry_t iface_table[] =
{
    { "adc_pot", &adc_pot_ctx },
    { "pwm_led", &pwm_led_ctx }
};

const InterfaceEntry_t* interfaces_get_table(size_t *count)
{
    *count = sizeof(iface_table) / sizeof(iface_table[0]);
    return iface_table;
}
