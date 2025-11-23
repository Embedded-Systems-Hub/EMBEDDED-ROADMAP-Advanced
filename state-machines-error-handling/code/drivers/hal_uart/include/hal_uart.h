#ifndef HAL_UART_H
#define HAL_UART_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "error_codes.h"

typedef struct
{
    status_t (*init)(void *ctx, uint32_t baudrate);
    status_t (*write)(void *ctx, const uint8_t *data, size_t len);
    status_t (*read)(void *ctx, uint8_t *data, size_t len);
} HAL_Uart_Driver_t;

status_t hal_uart_init(void *ctx, uint32_t baudrate);
status_t hal_uart_write(void *ctx, const uint8_t *data, size_t len);
status_t hal_uart_read(void *ctx, uint8_t *data, size_t len);

const HAL_Uart_Driver_t* hal_uart_get_drv(void);

#endif
