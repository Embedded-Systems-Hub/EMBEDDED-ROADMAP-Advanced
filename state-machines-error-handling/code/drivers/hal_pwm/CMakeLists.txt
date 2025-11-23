add_library(hal_pwm_lib
    src/hal_pwm.c
    cfg/hal_pwm_cfg.c
)

target_link_libraries(hal_pwm_lib
    common_lib
)

target_include_directories(hal_pwm_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
