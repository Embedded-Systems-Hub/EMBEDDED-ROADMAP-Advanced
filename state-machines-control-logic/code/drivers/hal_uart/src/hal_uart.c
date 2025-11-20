#include "hal_uart.h"
#include <stdio.h>

static const HAL_Uart_Driver_t *s_drv = NULL;

int hal_uart_init(void *ctx, uint32_t baudrate)
{
    s_drv = hal_uart_get_drv();
    return s_drv ? s_drv->init(ctx, baudrate) : -1;
}

int hal_uart_write(void *ctx, const uint8_t *data, size_t len)
{
    return s_drv ? s_drv->write(ctx, data, len) : -1;
}

int hal_uart_read(void *ctx, uint8_t *data, size_t len)
{
    return s_drv ? s_drv->read(ctx, data, len) : -1;
}
