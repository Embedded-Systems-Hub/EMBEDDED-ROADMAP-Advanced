add_library(hal_led_lib
    src/hal_led.c
    cfg/hal_led_cfg.c
)

target_link_libraries(hal_led_lib
    hal_gpio_lib
    common_lib
)

target_include_directories(hal_led_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
