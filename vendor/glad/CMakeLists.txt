cmake_minimum_required(VERSION 3.25.1)
project(glad)

option(BUILD_SHARED_LIBS OFF)

if(${BUILD_SHARED_LIBS})
    add_library(glad SHARED "src/glad.c")
else()
    add_library(glad STATIC "src/glad.c")
endif()

target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")