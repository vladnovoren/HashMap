cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

project(HashTable VERSION 1.0 LANGUAGES CXX)

# set(CMAKE_CXX_COMPILER g++)
# set(FLAGS "-Wall -Wextra -g")

add_subdirectory(ONEGIN_lib)
add_subdirectory(List)

include_directories(include/ ONEGIN_lib/include List/include)


add_executable(hash_table src/main.cpp src/hash_table.cpp src/dic_parser.cpp src/test_hash_table.cpp src/hash_functions.cpp)
add_executable(dic_parser src/dic_parser.cpp src/test_parser.cpp)

set(CMAKE_CXX_FLAGS ${FLAGS})

install(TARGETS dic_parser DESTINATION {CMAKE_SOURCE_DIR}/bin/)

target_link_libraries(hash_table List)
target_link_libraries(hash_table ONEGIN_lib)
target_link_libraries(dic_parser ONEGIN_lib)

set_target_properties( dic_parser hash_table
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
