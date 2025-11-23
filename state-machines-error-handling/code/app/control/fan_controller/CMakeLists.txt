add_library(fan_controller_lib
    src/fan_controller.c
)

target_link_libraries(fan_controller_lib PUBLIC
    sensors_lib
    actuators_lib
    logger_lib
    common_lib
)

target_include_directories(fan_controller_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
