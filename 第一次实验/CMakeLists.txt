cmake_minimum_required(VERSION 3.16)
project(Bezier_Curve)

set(CMAKE_CXX_STANDARD 20)

add_executable(Bezier_Curve main.cpp)
target_link_libraries(Bezier_Curve libopengl32.a  libfreeglut.a)