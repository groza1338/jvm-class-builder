cmake_minimum_required(VERSION 4.1)
project(jvm_class_builder_)

set(CMAKE_CXX_STANDARD 20)

add_library(jvm_class_builder_ STATIC library.cpp)
