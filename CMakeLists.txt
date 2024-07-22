cmake_minimum_required(VERSION 3.2)

project( blinkt )

set (CMAKE_C_STANDARD 11 )
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/ )
set (CMAKE_BUILD_TYPE Debug )

include_directories( blinkt.out PRIVATE src )

add_executable( blinkt.out
                src/main.c)

target_compile_options( blinkt.out
                        PUBLIC
                        -Wfatal-errors
                        -Wall
                        -Wextra
                        -Werror
                        -Wpedantic
                        -Wpointer-arith
                        -g)
