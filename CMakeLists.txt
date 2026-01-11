cmake_minimum_required(VERSION 3.20)

project(jvm-class-builder
        VERSION 0.1.0
        DESCRIPTION "Structured JVM class file builder."
        LANGUAGES CXX
)

option(BUILD_SHARED_LIBS "Build libraries as shared" OFF)

add_library(jvm-class-builder
        include/jvm/serializable.h
        include/jvm/owner-aware.h
        src/class.cpp
        src/constant.cpp
        src/constant-utf-8-info.cpp
        src/constant-class.cpp
        src/constant-name-and-type.cpp
        src/constant-fieldref.cpp
        src/constant-methodref.cpp
        src/constant-interface-methodref.cpp
        src/constant-string.cpp
        src/constant-integer.cpp
        src/constant-float.cpp
        src/constant-double.cpp
        src/constant-long.cpp
        src/field.cpp
        src/method.cpp
        src/attribute.cpp
        src/attribute-code.cpp
        src/instruction.cpp
        src/instruction-jump.cpp
        src/instruction-ldc.cpp
        src/instruction-with-constant.cpp
        src/label.cpp
        src/exception-handler.cpp
        src/internal/utils.cpp
        src/descriptor.cpp
        src/descriptor-field.cpp
        src/descriptor-method.cpp
)

target_compile_features(jvm-class-builder PUBLIC cxx_std_20)
set_target_properties(jvm-class-builder PROPERTIES
        CXX_EXTENSIONS OFF
        EXPORT_NAME ClassBuilder
)

target_include_directories(jvm-class-builder
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal
)

add_library(jvm::ClassBuilder ALIAS jvm-class-builder)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS jvm-class-builder
        EXPORT jvm-class-builderTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT jvm-class-builderTargets
        FILE jvm-class-builderTargets.cmake
        NAMESPACE jvm::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/jvm-class-builder
)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/jvm-class-builderConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/jvm-class-builderConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/jvm-class-builderConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/jvm-class-builder
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/jvm-class-builderConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/jvm-class-builderConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/jvm-class-builder
)
