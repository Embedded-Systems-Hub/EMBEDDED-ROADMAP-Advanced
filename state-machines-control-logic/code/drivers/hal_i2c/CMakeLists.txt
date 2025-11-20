add_library(hal_i2c_lib
    src/hal_i2c.c
    cfg/hal_i2c_cfg.c
)

target_include_directories(hal_i2c_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
