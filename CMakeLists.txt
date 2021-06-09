cmake_minimum_required(VERSION 3.0)

project(avan)
enable_testing()

add_subdirectory(deps)  # add project dependencies
add_subdirectory(cores) # add console cores

add_executable(avan src/main.c)
target_link_libraries(avan PUBLIC gameboy)

add_library(avan-lib INTERFACE)
target_include_directories(avan-lib INTERFACE include)