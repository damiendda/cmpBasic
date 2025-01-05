cmake_minimum_required(VERSION 3.30)

project(cmpBasic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(SOURCES main.cpp lexer.cpp lexer.h parser.cpp parser.h)

add_executable(main ${SOURCES})
