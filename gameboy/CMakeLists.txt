project(gameboy)

file(GLOB SOURCE_FILES src/*.c)
file(GLOB TEST_FILES tests/*.c)

include_directories(src include ../include)
add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include)

add_executable(${PROJECT_NAME}_test ${TEST_FILES})
target_link_libraries(${PROJECT_NAME}_test PUBLIC gameboy)
add_test(${PROJECT_NAME}_test ${PROJECT_NAME}_test)
