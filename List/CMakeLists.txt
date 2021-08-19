cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

set(FLAGS "-Wall -Wextra -g")

project(list)
add_executable(list src/main.cpp src/list.cpp src/list_dump.cpp)
add_executable(test_stl src/test_stl.cpp)
add_executable(test_my_list src/test_my_list.cpp src/list.cpp)

add_library(List STATIC src/list.cpp)

include_directories(include)

set_target_properties(list test_stl test_my_list
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)