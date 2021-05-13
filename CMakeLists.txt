cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

project(HashTable VERSION 1.0 LANGUAGES CXX)


set(FLAGS "-Wall -Wextra -g -fsanitize=address")
set(CMAKE_CXX_FLAGS ${FLAGS})

add_subdirectory(ONEGIN_lib)
add_subdirectory(List)

include_directories(include/ ONEGIN_lib/include List/include)


add_executable(hash_table src/main.cpp src/hash_table.cpp src/dic_parser.cpp src/test_hash_functions.cpp)

target_link_libraries(hash_table ONEGIN_lib)
target_link_libraries(hash_table List)

