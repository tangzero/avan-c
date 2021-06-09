cmake_minimum_required(VERSION 3.0)

project(avan)
enable_testing()

add_subdirectory(deps)  # add project dependencies
add_subdirectory(cores) # add console cores

add_executable(avan src/main.c)
target_link_libraries(avan PUBLIC gameboy)
