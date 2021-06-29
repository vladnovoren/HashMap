cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

project(HashTable VERSION 1.0 LANGUAGES CXX)


<<<<<<< HEAD
set(FLAGS "-Wall -Wextra")
=======
set(FLAGS "-Wall -Wextra -g -fsanitize=address")
set(CMAKE_CXX_FLAGS ${FLAGS})
>>>>>>> 20a61fa764bdd7dbc113b42b459ae53aaadbbf4e

add_subdirectory(ONEGIN_lib)
add_subdirectory(List)

include_directories(include/ ONEGIN_lib/include List/include)


<<<<<<< HEAD
add_executable(hash_table src/main.cpp src/hash_table.cpp src/dic_parser.cpp)
add_executable(dic_parser src/dic_parser.cpp src/test_parser.cpp)

set(CMAKE_CXX_FLAGS ${FLAGS})

=======
add_executable(hash_table src/main.cpp src/hash_table.cpp src/dic_parser.cpp src/test_hash_functions.cpp)
>>>>>>> 20a61fa764bdd7dbc113b42b459ae53aaadbbf4e

target_link_libraries(hash_table ONEGIN_lib)
target_link_libraries(dic_parser ONEGIN_lib)
target_link_libraries(hash_table List)
