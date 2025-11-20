add_library(hal_uart_lib
    src/hal_uart.c
    cfg/hal_uart_cfg.c
)

target_include_directories(hal_uart_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
