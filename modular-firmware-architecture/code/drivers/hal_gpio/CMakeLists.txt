add_library(hal_gpio_lib
    src/hal_gpio.c
    cfg/hal_gpio_cfg.c
)

target_include_directories(hal_gpio_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
