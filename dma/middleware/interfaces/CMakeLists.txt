add_library(interfaces_lib
    src/interfaces.c
    cfg/interfaces_cfg.c
)

target_link_libraries(interfaces_lib
    drivers_lib
)

target_include_directories(interfaces_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
