cmake_minimum_required(VERSION 3.10)
project(spring C)

set(CMAKE_C_STANDARD 99)

find_package(raylib REQUIRED)

add_executable(spring spring.c)
target_link_libraries(spring raylib)
