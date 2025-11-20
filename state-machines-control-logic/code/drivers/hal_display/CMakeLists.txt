add_library(hal_display_lib
    src/hal_display.c
    cfg/hal_display_cfg.c
)

target_link_libraries(hal_display_lib
    hal_uart_lib
)

target_include_directories(hal_display_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
