#include "hal_gpio.h"
#include "error_codes.h"

static const HAL_GPIO_Driver_t *s_drv = NULL;

status_t hal_gpio_init(void *ctx, uint8_t pin, HAL_GPIO_Direction_t dir)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);

    s_drv = hal_gpio_get_drv();
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->init);

    CHECK_STATUS(s_drv->init(ctx, pin, dir));

    return ret;
}

status_t hal_gpio_write(void *ctx, uint8_t pin, uint8_t value)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->write);

    CHECK_STATUS(s_drv->write(ctx, pin, value));

    return ret;
}

status_t hal_gpio_read(void *ctx, uint8_t pin, uint8_t *value)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(value);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->read);

    CHECK_STATUS(s_drv->read(ctx, pin, value));

    return ret;
}
