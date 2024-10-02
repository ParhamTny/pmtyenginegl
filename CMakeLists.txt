cmake_minimum_required(VERSION 3.28)

project(pmtyenginegl VERSION 1.0)

list(APPEND PMTYENGINEGL_DEPENDENCIES glfw glad glm)

foreach(dependency IN LISTS PMTYENGINEGL_DEPENDENCIES)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dependencies/${dependency}")
endforeach()

add_subdirectory(pmtyenginegl)
add_subdirectory(game)