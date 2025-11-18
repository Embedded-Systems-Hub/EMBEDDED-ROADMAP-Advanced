#include "hal_display.h"
#include "hal_uart.h"
#include <stdio.h>

typedef struct { void *uart_ctx; } HAL_Display_Device_t;

static int display_init_wrapper(void *dev)
{
    HAL_Display_Device_t *d = dev;

#ifdef TARGET_HOST
    printf("[DISPLAY_CFG] init dev=%p uart_ctx=%p baud=115200\n",
           d, d->uart_ctx);
#endif

    return hal_uart_init(d->uart_ctx, 115200);
}

static int display_write_wrapper(void *dev, const uint8_t *data, size_t len)
{
    HAL_Display_Device_t *d = dev;

#ifdef TARGET_HOST
    printf("[DISPLAY_CFG] write dev=%p uart_ctx=%p len=%zu: \"",
           d, d->uart_ctx, len);
    for (size_t i = 0; i < len; i++)
        printf("%c", data[i]);
    printf("\"\n");
#endif

    return hal_uart_write(d->uart_ctx, data, len);
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
