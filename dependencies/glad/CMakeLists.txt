cmake_minimum_required(VERSION 3.28)

add_library(glad STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/gl.c" "${CMAKE_CURRENT_SOURCE_DIR}/include/glad/gl.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h")

target_include_directories(glad PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")