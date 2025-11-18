add_library(hal_fan_lib
    src/hal_fan.c
    cfg/hal_fan_cfg.c
)

target_link_libraries(hal_fan_lib
    hal_gpio_lib
)

target_include_directories(hal_fan_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
