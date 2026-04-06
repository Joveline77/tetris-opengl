cmake_minimum_required(VERSION 3.14)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_library(glad STATIC libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

add_executable(Tetris src/main.cpp)

target_link_libraries(Tetris PRIVATE glfw glad)

target_include_directories(
  Tetris PRIVATE ${GLM_INCLUDE_DIRS}
  Tetris PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)
