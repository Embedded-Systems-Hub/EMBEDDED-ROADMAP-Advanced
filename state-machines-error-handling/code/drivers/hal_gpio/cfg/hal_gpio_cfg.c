#include "hal_gpio.h"
#include "error_codes.h"

static status_t gpio_init_wrapper(void *ctx, uint8_t pin, HAL_GPIO_Direction_t dir)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);

#ifdef TARGET_HOST
    printf("[GPIO_CFG] init ctx=%p pin=%u dir=%u\n",
           ctx, pin, dir);
#endif

    return ret;
}

static status_t gpio_write_wrapper(void *ctx, uint8_t pin, uint8_t value)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);

#ifdef TARGET_HOST
    printf("[GPIO_CFG] write ctx=%p pin=%u val=%u\n",
           ctx, pin, value);
#endif

    return ret;
}

static status_t gpio_read_wrapper(void *ctx, uint8_t pin, uint8_t *value)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(value);

#ifdef TARGET_HOST
    printf("[GPIO_CFG] read ctx=%p pin=%u → *value=0\n",
           ctx, pin);
#endif

    *value = 0U;

    return ret;
}

static const HAL_GPIO_Driver_t gpio_driver =
{
    .init  = gpio_init_wrapper,
    .write = gpio_write_wrapper,
    .read  = gpio_read_wrapper
};

const HAL_GPIO_Driver_t* hal_gpio_get_drv(void)
{
    return &gpio_driver;
}
