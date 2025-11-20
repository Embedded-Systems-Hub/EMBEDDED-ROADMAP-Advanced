add_library(light_controller_lib
    src/light_controller.c
)

target_link_libraries(light_controller_lib PUBLIC
    sensors_lib
    actuators_lib
    logger_lib
)

target_include_directories(light_controller_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
