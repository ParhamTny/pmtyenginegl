cmake_minimum_required(VERSION 3.28)

file(GLOB PMTYENGINEGL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/include/pmtyenginegl/*.h")

find_package(OpenGL REQUIRED)

if (NOT OpenGL_FOUND)
	message(FATAL_ERROR "failed to find opengl")
endif()

add_library(pmtyenginegl STATIC ${PMTYENGINEGL_SOURCES})

set_property(TARGET pmtyenginegl PROPERTY CXX_STANDARD 20)

target_include_directories(pmtyenginegl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_SOURCE_DIR}/dependencies/glfw/include" "${CMAKE_SOURCE_DIR}/dependencies/glad/include"
	"${CMAKE_SOURCE_DIR}/dependencies/glm")

target_link_libraries(pmtyenginegl PRIVATE OpenGL::GL glfw glad)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/include/pmtyenginegl/version.h")