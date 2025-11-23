#include "hal_i2c.h"
#include "error_codes.h"

static const HAL_I2C_Driver_t *s_drv = NULL;

status_t hal_i2c_init(void *ctx)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);

    s_drv = hal_i2c_get_drv();
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->init);

    CHECK_STATUS(s_drv->init(ctx));

    return ret;
}

status_t hal_i2c_write(void *ctx, uint8_t addr, const uint8_t *data, size_t len)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(data);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->write);

    CHECK_STATUS(s_drv->write(ctx, addr, data, len));

    return ret;
}

status_t hal_i2c_read(void *ctx, uint8_t addr, uint8_t *data, size_t len)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(data);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->read);

    CHECK_STATUS(s_drv->read(ctx, addr, data, len));

    return ret;
}
