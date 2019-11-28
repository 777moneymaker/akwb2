cmake_minimum_required(VERSION 3.15)
project(akwb2)

set(CMAKE_CXX_STANDARD 14)

include_directories(Data)
include_directories(Libraries)

add_executable(akwb2
        cmake-build-debug/sample.fasta
        cmake-build-debug/qualities.qual
        Libraries/Vertex.cpp
        Libraries/Vertex.hpp
        LICENSE
        main.cpp
        README.md Libraries/Graph.cpp Libraries/Graph.hpp)
