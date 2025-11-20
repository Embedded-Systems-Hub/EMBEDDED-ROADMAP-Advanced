add_subdirectory(control)

add_library(app_lib INTERFACE)

target_link_libraries(app_lib INTERFACE
    control_lib
)

target_include_directories(app_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
