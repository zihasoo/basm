cmake_minimum_required(VERSION 3.25)
project(basm)

set(CMAKE_CXX_STANDARD 20)

add_executable(basm basm.cpp Lexer.h Lexer.cpp basm.cpp)
