#include "hal_uart.h"
#include "error_codes.h"

static status_t uart_init_wrapper(void *ctx, uint32_t baudrate)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);

#ifdef TARGET_HOST
    printf("[UART_CFG] init ctx=%p baud=%u\n", ctx, baudrate);
#endif

    return ret;
}

static status_t uart_write_wrapper(void *ctx, const uint8_t *data, size_t len)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(data);

#ifdef TARGET_HOST
    printf("[UART_CFG] write ctx=%p len=%zu : ", ctx, len);
    for (size_t i = 0; i < len; i++)
        printf("%02X ", data[i]);
    printf("\n");
#endif

    return ret;
}

static status_t uart_read_wrapper(void *ctx, uint8_t *data, size_t len)
{
    status_t ret = STATUS_OK;

    CHECK_NULL(ctx);
    CHECK_NULL(data);

#ifdef TARGET_HOST
    printf("[UART_CFG] read ctx=%p len=%zu\r\n", ctx, len);
#endif

    for (size_t i = 0; i < len; i++)
        data[i] = 0U;

    return ret;
}

static const HAL_Uart_Driver_t uart_driver =
{
    .init  = uart_init_wrapper,
    .write = uart_write_wrapper,
    .read  = uart_read_wrapper
};

const HAL_Uart_Driver_t* hal_uart_get_drv(void)
{
    return &uart_driver;
}
