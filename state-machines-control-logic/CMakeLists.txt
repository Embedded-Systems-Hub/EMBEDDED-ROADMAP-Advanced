cmake_minimum_required(VERSION 3.22.1)
project(weather_station C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Werror)

if (TARGET_HOST)
    add_compile_definitions(TARGET_HOST)
endif()

add_subdirectory(code)
