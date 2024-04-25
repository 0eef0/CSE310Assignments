cmake_minimum_required(VERSION 3.26)
project(Assignment_8)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment_8
        Assignment8.cpp
        Edge.h
        Graph.h)
