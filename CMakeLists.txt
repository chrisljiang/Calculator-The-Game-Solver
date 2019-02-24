cmake_minimum_required(VERSION 3.12)
project(CalculatorGame)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(CalculatorGame main.cpp rules.h rules.cpp ops.h ops.cpp opsenum.h sol.h sol.cpp extrafunc.h extrafunc.cpp)