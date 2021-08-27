cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

project(HashMap VERSION 1.0 LANGUAGES CXX)

set(FLAGS "-Wall -Wextra -g -O3")

add_subdirectory(ONEGIN_lib)
add_subdirectory(List)

add_library(HashMap STATIC src/hash_map.cpp src/hash_funcs.cpp src/test_hash_map.cpp)
add_library(DicParser STATIC src/dic_parser.cpp)

include_directories(include/ ONEGIN_lib/include List/include)

add_executable(test_hash_funcs  src/test_hash_funcs.cpp)
add_executable(test_parser src/test_parser.cpp)
add_executable(test_speed  src/test_speed.cpp)

set(CMAKE_CXX_FLAGS ${FLAGS})

target_link_libraries(DicParser ONEGIN_lib)
target_link_libraries(HashMap DicParser List)

target_link_libraries(test_parser     DicParser)
target_link_libraries(test_hash_funcs HashMap)
target_link_libraries(test_speed      HashMap)

set_target_properties(test_parser test_hash_funcs test_speed
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
