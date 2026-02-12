cmake_minimum_required(VERSION 3.29)
project(PF_PROJECT)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PF_PROJECT
    laboratory.h
    main.cpp
        Laboratory1.h
        Laboratory1.cpp)
