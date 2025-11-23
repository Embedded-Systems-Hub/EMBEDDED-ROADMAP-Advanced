add_library(storage_lib
    src/storage.c
    cfg/storage_cfg.c
)

target_link_libraries(storage_lib
    interfaces_lib
    drivers_lib
    common_lib
)

target_include_directories(storage_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
