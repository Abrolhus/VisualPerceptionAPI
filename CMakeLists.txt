set (CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 2.8)
project(visualPerception)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
find_package(OpenCV REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_subdirectory(src)
add_subdirectory(test)
