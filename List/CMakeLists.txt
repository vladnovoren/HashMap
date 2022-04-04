cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

set(FLAGS "-Wall -Wextra -g")

project(list)

add_library(List STATIC src/list.cpp)

target_include_directories(List PUBLIC include/)