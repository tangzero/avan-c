cmake_minimum_required(VERSION 3.0)

project(avan)
enable_testing()

add_subdirectory(deps/Unity)
add_subdirectory(gameboy)

add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME} PUBLIC gameboy)
