cmake_minimum_required(VERSION 3.15)
project(noname)

set(CPP_TEST_OPTIONS -std=c++20 -W -Wall -Wextra -Wpedantic)
set(CPP_COMPILE_OPTIONS ${CPP_TEST_OPTIONS} -Werror)

add_executable(emulator emulator.cpp 6502.cpp)
target_compile_options(emulator PRIVATE -g ${CPP_COMPILE_OPTIONS})