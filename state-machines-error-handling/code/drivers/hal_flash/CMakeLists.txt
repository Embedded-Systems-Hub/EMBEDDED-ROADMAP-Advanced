add_library(hal_flash_lib
    src/hal_flash.c
    cfg/hal_flash_cfg.c
)

target_link_libraries(hal_flash_lib
    hal_spi_lib
    common_lib
)

target_include_directories(hal_flash_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
