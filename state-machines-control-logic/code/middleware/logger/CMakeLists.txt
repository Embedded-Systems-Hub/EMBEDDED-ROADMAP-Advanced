add_library(logger_lib
    src/logger.c
    cfg/logger_cfg.c
)

target_link_libraries(logger_lib
    actuators_lib
    storage_lib
)

target_include_directories(logger_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
