cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

project(HashTable VERSION 1.0 LANGUAGES CXX)

set(FLAGS "-Wall -Wextra -Werror -g")

add_subdirectory(ONEGIN_lib)
add_subdirectory(List)

add_library(HashTable STATIC src/hash_table src/hash_functions.cpp)

include_directories(include/ ONEGIN_lib/include List/include)

add_executable(hash_table  src/main.cpp src/test_hash_table.cpp src/dic_parser.cpp)
add_executable(dic_parser  src/dic_parser.cpp src/test_parser.cpp)
add_executable(test_parser src/test_parser.cpp src/dic_parser.cpp)

set(CMAKE_CXX_FLAGS ${FLAGS})

install(TARGETS dic_parser DESTINATION {CMAKE_SOURCE_DIR}/bin/)

target_link_libraries(dic_parser ONEGIN_lib)
target_link_libraries(test_parser ONEGIN_lib List)
target_link_libraries(HashTable ONEGIN_lib List)
target_link_libraries(hash_table HashTable)

set_target_properties( dic_parser hash_table test_parser 
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
