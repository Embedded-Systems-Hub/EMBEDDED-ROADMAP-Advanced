add_subdirectory(app)
add_subdirectory(drivers)
add_subdirectory(middleware)

add_executable(weather_station
    app/main.c
)

set_target_properties(weather_station PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_libraries(weather_station
    app_lib
    middleware_lib
    drivers_lib
)
