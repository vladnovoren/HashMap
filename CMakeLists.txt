cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

project(HashTable VERSION 1.0 LANGUAGES CXX)

add_subdirectory(ONEGIN_lib)

include_directories(include/ ONEGIN_lib/include)
