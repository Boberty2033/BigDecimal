cmake_minimum_required(VERSION 3.29)
project(Big_decimal)

set(CMAKE_CXX_STANDARD 20)

add_executable(Big_decimal main.cpp
        big_decimal.cpp
        big_decimal.h
        test.cpp)
