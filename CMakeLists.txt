cmake_minimum_required(VERSION 3.21)
project(cpp_project_2021h1)

set(CMAKE_CXX_STANDARD 14)

include_directories(Geometry)

add_executable(cpp_project_2021h1
        Geometry/Circle.cpp
        Geometry/Circle.h
        Geometry/Curve.cpp
        Geometry/Curve.hpp
        Geometry/Figure2D.cpp
        Geometry/Figure2D.h
        Geometry/Figure3D.cpp
        Geometry/Figure3D.h
        Geometry/GeometricObject.cpp
        Geometry/GeometricObject.h
        Geometry/Geometry.cpp
        Geometry/Line.cpp
        Geometry/Line.hpp
        Geometry/Menu.cpp
        Geometry/Menu.h
        Geometry/Point.cpp
        Geometry/Point.h
        Geometry/Straight.cpp
        Geometry/Straight.hpp)
