cmake_minimum_required(VERSION 3.16)
project(CG)

set(CMAKE_CXX_STANDARD 14)

add_executable(light main.cpp Color.h Light.h Ray.h Object.h Sphere.h Sphere.cpp Vector3d.h Vector3d.cpp Cube.h Cube.cpp)
target_link_libraries(light libopengl32.a  libfreeglut.a libglu32.a)