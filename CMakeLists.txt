cmake_minimum_required(VERSION 4.1)
project(jvm_class_builder_)

set(CMAKE_CXX_STANDARD 20)

set(HEADERS
        src/class.h
        src/constant.h
        src/constant-utf-8-info.h
)

set(SOURCE
        src/class.cpp
        src/constant.cpp
        src/constant-utf-8-info.cpp
)

add_library(jvm_c STATIC
        ${HEADERS}
        ${SOURCE}
)
