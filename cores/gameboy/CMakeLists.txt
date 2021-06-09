project(gameboy)

file(GLOB source_files src/*.c)
file(GLOB test_files tests/*.c)

include_directories(src include)
add_library(gameboy ${source_files})
target_link_libraries(gameboy PUBLIC base-core)
target_include_directories(gameboy PUBLIC include)

foreach (filename ${test_files})
    get_filename_component(name ${filename} NAME_WLE)
    message("adding test suite to the gameboy core: ${name}")
    add_executable(${name} ${filename})
    target_link_libraries(${name} PUBLIC gameboy unity)
    add_test(${name} ${name})
endforeach ()
