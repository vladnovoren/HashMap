cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

set(FLAGS "-Wall -Wextra -g")

add_library(List STATIC src/list.cpp)

include_directories(include)

set_target_properties(List PROPERTIES LINKER_LANGUAGE CXX)
