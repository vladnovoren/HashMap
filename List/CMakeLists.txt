cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

add_library(List STATIC src/list.cpp)


include_directories(List ../ONEGIN_lib/include/ include/)
