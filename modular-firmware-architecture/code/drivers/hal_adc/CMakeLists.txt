add_library(hal_adc_lib
    src/hal_adc.c
    cfg/hal_adc_cfg.c
)

target_include_directories(hal_adc_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
