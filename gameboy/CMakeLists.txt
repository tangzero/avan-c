project(gameboy)

file(GLOB source_files src/*.c)
file(GLOB test_files tests/*.c)

include_directories(src include ../include)
add_library(${PROJECT_NAME} ${source_files})
target_include_directories(${PROJECT_NAME} PUBLIC include)

macro(test_suite filename)
    get_filename_component(name ${filename} NAME_WLE)
    message("adding the test suite: ${name}")
    add_executable(${name} ${filename})
    target_link_libraries(${name} PUBLIC gameboy unity)
    add_test(${name} ${name})
endmacro()

foreach(filename ${test_files})
    test_suite(${filename})
endforeach()