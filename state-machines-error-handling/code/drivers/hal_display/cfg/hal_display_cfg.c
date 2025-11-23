#include "hal_display.h"
#include "hal_uart.h"
#include "error_codes.h"

typedef struct { void *uart_ctx; } HAL_Display_Device_t;

static status_t display_init_wrapper(void *dev)
{
    status_t ret = STATUS_OK;
    HAL_Display_Device_t *d = dev;

    CHECK_NULL(d);
    CHECK_NULL(d->uart_ctx);

#ifdef TARGET_HOST
    printf("[DISPLAY_CFG] init dev=%p uart_ctx=%p baud=115200\n",
           d, d->uart_ctx);
#endif

    CHECK_STATUS(hal_uart_init(d->uart_ctx, 115200));

    return ret;
}

static status_t display_write_wrapper(void *dev, const uint8_t *data, size_t len)
{
    status_t ret = STATUS_OK;
    HAL_Display_Device_t *d = dev;

    CHECK_NULL(d);
    CHECK_NULL(d->uart_ctx);
    CHECK_NULL(data);

#ifdef TARGET_HOST
    printf("[DISPLAY_CFG] write dev=%p uart_ctx=%p len=%zu: \n",
           d, d->uart_ctx, len);
    for (size_t i = 0; i < len; i++)
        printf("%c", data[i]);
    printf("\n");
#endif

    CHECK_STATUS(hal_uart_write(d->uart_ctx, data, len));

    return ret;
}

static const HAL_Display_Driver_t display_driver =
{
    .init  = display_init_wrapper,
    .write = display_write_wrapper
};

const HAL_Display_Driver_t* hal_display_get_drv(void)
{
    return &display_driver;
}
