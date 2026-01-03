cmake_minimum_required(VERSION 4.1)
project(jvm_class_builder_)

set(CMAKE_CXX_STANDARD 20)

set(HEADERS
        src/class.h
        src/constant.h
        src/constant-utf-8-info.h
        src/constant-class.h
        src/constant-name-and-type.h
        src/constant-fieldref.h
        src/constant-methodref.h
        src/constant-interface-methodref.h
        src/constant-string.h
        src/constant-integer.h
        src/constant-float.h
        src/constant-double.h
        src/field.h
        src/method.h
        src/attribute.h
)

set(SOURCE
        src/class.cpp
        src/constant.cpp
        src/constant-utf-8-info.cpp
        src/constant-class.cpp
        src/constant-name-and-type.cpp
        src/constant-fieldref.cpp
        src/constant-methodref.h
        src/constant-interface-methodref.cpp
        src/constant-string.cpp
        src/constant-integer.cpp
        src/constant-float.cpp
        src/constant-double.cpp
        src/field.cpp
        src/method.cpp
        src/attribute.cpp
)

add_library(jvm_c STATIC
        ${HEADERS}
        ${SOURCE}
)
