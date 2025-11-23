#include "interfaces.h"

#include "hal_adc.h"
#include "hal_gpio.h"
#include "hal_i2c.h"
#include "hal_spi.h"
#include "hal_uart.h"

#include <stdio.h>

/*
 * Each hardware block gets a context object.
 * These structs can later hold chip-specific state,
 * DMA handles, interrupt configuration, buffers, etc.
 * 
 * For now they are empty because HOST mode only simulates hardware.
 */
typedef struct { void *hw; } I2C_Context_t;
typedef struct { void *hw; } ADC_Context_t;
typedef struct { void *hw; } GPIO_Context_t;
typedef struct { void *hw; } SPI_Context_t;
typedef struct { void *hw; } UART_Context_t;
typedef struct { void *hw; } TIM_Context_t;

/* Static contexts for each interface instance. */
static I2C_Context_t  i2c1_ctx;
static ADC_Context_t  adc1_ctx;
static GPIO_Context_t gpioA_ctx;
static GPIO_Context_t gpioB_ctx;
static SPI_Context_t  spi1_ctx;
static UART_Context_t uart1_ctx;
static TIM_Context_t  pwm1_ctx;

void interfaces_cfg_init(void)
{
#ifdef TARGET_HOST
    printf("[INTERFACES_CFG] init\n");
#endif

    interfaces_register("i2c1",  &i2c1_ctx);
    interfaces_register("adc1",  &adc1_ctx);
    interfaces_register("gpioA", &gpioA_ctx);
    interfaces_register("gpioB", &gpioB_ctx);
    interfaces_register("spi1",  &spi1_ctx);
    interfaces_register("uart1", &uart1_ctx);
    interfaces_register("pwm1", &pwm1_ctx);
}
