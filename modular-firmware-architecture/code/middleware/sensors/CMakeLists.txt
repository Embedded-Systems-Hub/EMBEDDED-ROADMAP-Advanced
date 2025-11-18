add_library(sensors_lib
    src/sensors.c
    cfg/sensors_cfg.c
)

target_link_libraries(sensors_lib
    interfaces_lib
    drivers_lib
)

target_include_directories(sensors_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
