add_library(hal_spi_lib
    src/hal_spi.c
    cfg/hal_spi_cfg.c
)

target_link_libraries(hal_spi_lib
    common_lib
)

target_include_directories(hal_spi_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
