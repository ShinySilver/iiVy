cmake_minimum_required(VERSION 3.21)
project (iiVy C)
set(CMAKE_C_STANDARD 23)

include_directories(src)
set(dir ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir}/..)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
set_source_files_properties(${SRC_FILES} PROPERTIES CMAKE_C_FLAGS "-std=c2x") #c2x is a synonym for iso9899:2024 or c23, depending on gcc version
set_source_files_properties(${SRC_FILES} PROPERTIES CMAKE_C_FLAGS_RELEASE "-O3 -static")
set_source_files_properties(${SRC_FILES} PROPERTIES CMAKE_C_FLAGS_DEBUG
            "-g3  -O0 -Wall -Werror -Wshadow -Warray-bounds -Wcast-align=strict -Wstrict-prototypes -Wmissing-prototypes \
             -Wwrite-strings -Winit-self -Wold-style-definition -Wno-missing-braces -Wno-unused-function \
             -Wno-incompatible-pointer-types -Wno-uninitialized -Wno-format-security -Wno-unused-but-set-variable -Wno-unused-variable \
             -Wno-format-zero-length -Wno-unused-parameter -Wno-comment -fsanitize=address -static-libasan")

add_executable(iiVy ${SRC_FILES})
target_compile_options(iiVy PRIVATE -fmacro-prefix-map=${CMAKE_CURRENT_SOURCE_DIR}/=)
target_compile_definitions(iiVy PRIVATE "DEBUG=$<IF:$<CONFIG:Debug>,1,0>")


## Raylib
add_subdirectory(libraries/raylib)
target_link_libraries(iiVy raylib)

## Physac
include_directories(libraries/Physac/src)
set_source_files_properties(/libraries/Physac/physac.h PROPERTIES COMPILE_FLAGS -w)