cmake_minimum_required(VERSION 3.22.1)
project(weather_station C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Werror)

option(LOG_MIN_SEVERITY_DISPLAY "Min severity for display sink" "LOG_INFO")
option(LOG_MIN_SEVERITY_FLASH   "Min severity for flash sink"   "LOG_WARN")

add_compile_definitions(
    LOG_MIN_SEVERITY_DISPLAY=${LOG_MIN_SEVERITY_DISPLAY}
    LOG_MIN_SEVERITY_FLASH=${LOG_MIN_SEVERITY_FLASH}
)

if (TARGET_HOST)
    add_compile_definitions(TARGET_HOST)
endif()

add_subdirectory(code)
