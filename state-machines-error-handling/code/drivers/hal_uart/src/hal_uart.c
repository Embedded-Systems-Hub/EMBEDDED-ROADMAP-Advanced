#include "hal_uart.h"
#include "error_codes.h"

static const HAL_Uart_Driver_t *s_drv = NULL;

status_t hal_uart_init(void *ctx, uint32_t baudrate)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);

    s_drv = hal_uart_get_drv();
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->init);

    CHECK_STATUS(s_drv->init(ctx, baudrate));

    return ret;
}

status_t hal_uart_write(void *ctx, const uint8_t *data, size_t len)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(data);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->write);

    CHECK_STATUS(s_drv->write(ctx, data, len));

    return ret;
}

status_t hal_uart_read(void *ctx, uint8_t *data, size_t len)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(data);
    CHECK_NULL(s_drv);
    CHECK_NULL(s_drv->read);

    CHECK_STATUS(s_drv->read(ctx, data, len));

    return ret;
}
