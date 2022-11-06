cmake_minimum_required(VERSION 3.20)
project(move_semantics)

set(CMAKE_CXX_STANDARD 20)

add_executable(move_semantics main.cpp my_string.h dynamic_array.h )

target_compile_options(move_semantics PRIVATE -Wall -Wextra -pedantic -g -O0 -fno-omit-frame-pointer -fsanitize=address -fsanitize-recover=address)
target_link_options(move_semantics PRIVATE -fsanitize=address)