cmake_minimum_required(VERSION 3.17)
project(5_coloration)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(5_coloration src/main.cpp src/vertex.cpp include/vertex.hpp src/edge.cpp include/edge.hpp src/graph.cpp include/graph.hpp src/utils.cpp include/utils.hpp)