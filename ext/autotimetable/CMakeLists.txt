cmake_minimum_required(VERSION 3.24)
project(Autotimetable)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(Autotimetable
        autotimetable.cpp
        autotimetable.hpp
        intrinsics.hpp
        json.hpp
        main.cpp
        )
