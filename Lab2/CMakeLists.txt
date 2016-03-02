cmake_minimum_required(VERSION 3.3)
project(WinAPI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Button.cpp Button.h EditText.cpp EditText.h)
add_executable(WinAPI ${SOURCE_FILES})