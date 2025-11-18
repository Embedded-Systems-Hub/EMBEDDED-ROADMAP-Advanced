add_subdirectory(actuators)
add_subdirectory(interfaces)
add_subdirectory(logger)
add_subdirectory(sensors)
add_subdirectory(storage)

add_library(middleware_lib INTERFACE)

target_link_libraries(middleware_lib INTERFACE
    actuators_lib
    interfaces_lib
    logger_lib
    sensors_lib
    storage_lib
)

target_include_directories(middleware_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
