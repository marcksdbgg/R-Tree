cmake_minimum_required(VERSION 3.25)
project(R_Tree)

set(CMAKE_CXX_STANDARD 17)

add_executable(R_Tree main.cpp RTree.cpp RTree.h)

target_link_libraries(R_Tree -lOpenGL32 -lfreeGLUT -lglu32)