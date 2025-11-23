#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdio.h>
#include <stdint.h>
#include "error_codes.h"

typedef enum
{
    HAL_GPIO_DIR_INPUT = 0,
    HAL_GPIO_DIR_OUTPUT
} HAL_GPIO_Direction_t;

typedef struct
{
    status_t (*init)(void *ctx, uint8_t pin, HAL_GPIO_Direction_t dir);
    status_t (*write)(void *ctx, uint8_t pin, uint8_t value);
    status_t (*read)(void *ctx, uint8_t pin, uint8_t *value);
} HAL_GPIO_Driver_t;

status_t hal_gpio_init(void *ctx, uint8_t pin, HAL_GPIO_Direction_t dir);
status_t hal_gpio_write(void *ctx, uint8_t pin, uint8_t value);
status_t hal_gpio_read(void *ctx, uint8_t pin, uint8_t *value);

const HAL_GPIO_Driver_t* hal_gpio_get_drv(void);

#endif
