cmake_minimum_required(VERSION 3.3)
project(WinAPI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Car.cpp Car.h Controller.cpp Controller.h TrafficLight.cpp TrafficLight.h Pedestrian.cpp Pedestrian.h)
add_executable(WinAPI ${SOURCE_FILES})