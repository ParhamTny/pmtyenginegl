cmake_minimum_required(VERSION 3.28)

file(GLOB GAME_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/include/game/*.h")

add_executable(game ${GAME_SOURCES})

set_property(TARGET game PROPERTY CXX_STANDARD 20)

set_property(TARGET game PROPERTY CXX_STANDARD 20)

target_include_directories(game PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(game PRIVATE pmtyenginegl)