cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

set(FLAGS "-Wall -Wextra -g")

<<<<<<< HEAD
project(list)

add_library(List STATIC src/list.cpp)

target_include_directories(List PUBLIC include/)
=======
add_library(List STATIC src/list.cpp)

include_directories(include)

set_target_properties(List PROPERTIES LINKER_LANGUAGE CXX)
>>>>>>> crc32
