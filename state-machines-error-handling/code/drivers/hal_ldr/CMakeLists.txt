add_library(hal_ldr_lib
    src/hal_ldr.c
    cfg/hal_ldr_cfg.c
)

target_link_libraries(hal_ldr_lib
    hal_adc_lib
    common_lib
)

target_include_directories(hal_ldr_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
