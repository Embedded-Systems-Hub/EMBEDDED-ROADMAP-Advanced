add_library(actuators_lib
    src/actuators.c
    cfg/actuators_cfg.c
)

target_link_libraries(actuators_lib
    interfaces_lib
    drivers_lib
)

target_include_directories(actuators_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
