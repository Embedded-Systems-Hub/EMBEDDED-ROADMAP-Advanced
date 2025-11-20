#ifndef HAL_UART_H
#define HAL_UART_H

#include <stdint.h>
#include <stddef.h>

typedef struct
{
    int (*init)(void *ctx, uint32_t baudrate);
    int (*write)(void *ctx, const uint8_t *data, size_t len);
    int (*read)(void *ctx, uint8_t *data, size_t len);
} HAL_Uart_Driver_t;

int hal_uart_init(void *ctx, uint32_t baudrate);
int hal_uart_write(void *ctx, const uint8_t *data, size_t len);
int hal_uart_read(void *ctx, uint8_t *data, size_t len);

const HAL_Uart_Driver_t* hal_uart_get_drv(void);

#endif
