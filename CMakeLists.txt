cmake_minimum_required(VERSION 4.1)
project(jvm_class_builder_)

set(CMAKE_CXX_STANDARD 20)

set(HEADERS
        src/class.h
)

set(SOURCE
        src/class.cpp
)

add_library(jvm_c STATIC
        ${HEADERS}
        ${SOURCE}
)
