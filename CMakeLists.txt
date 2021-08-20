cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

project(HashTable VERSION 1.0 LANGUAGES CXX)

set(FLAGS "-Wall -Wextra -g -O3")

add_subdirectory(ONEGIN_lib)
add_subdirectory(List)

add_library(HashTable STATIC src/hash_table.cpp src/hash_functions.cpp src/test_hash_table.cpp)
add_library(DicParser STATIC src/dic_parser.cpp)

include_directories(include/ ONEGIN_lib/include List/include)

add_executable(test_hash_functions  src/test_hash_functions.cpp)
add_executable(test_parser src/test_parser.cpp)
add_executable(test_speed  src/test_speed.cpp)

set(CMAKE_CXX_FLAGS ${FLAGS})

target_link_libraries(DicParser ONEGIN_lib)
target_link_libraries(HashTable DicParser List)

target_link_libraries(test_parser         DicParser)
target_link_libraries(test_hash_functions HashTable)
target_link_libraries(test_speed          HashTable)

set_target_properties(test_parser test_hash_functions test_speed
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
