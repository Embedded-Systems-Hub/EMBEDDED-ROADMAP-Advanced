#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdint.h>

typedef enum
{
    HAL_GPIO_DIR_INPUT = 0,
    HAL_GPIO_DIR_OUTPUT
} HAL_GPIO_Direction_t;

typedef struct
{
    int (*init)(void *ctx, uint8_t pin, HAL_GPIO_Direction_t dir);
    int (*write)(void *ctx, uint8_t pin, uint8_t value);
    int (*read)(void *ctx, uint8_t pin, uint8_t *value);
} HAL_GPIO_Driver_t;

int hal_gpio_init(void *ctx, uint8_t pin, HAL_GPIO_Direction_t dir);
int hal_gpio_write(void *ctx, uint8_t pin, uint8_t value);
int hal_gpio_read(void *ctx, uint8_t pin, uint8_t *value);

const HAL_GPIO_Driver_t* hal_gpio_get_drv(void);

#endif
