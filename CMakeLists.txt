cmake_minimum_required(VERSION 3.27)
project(Projekt_PEA_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projekt_PEA_3 main.cpp
        Algorithms/Algorithms.cpp
        Algorithms/Algorithms.h
        Main/Main.cpp
        Main/Menu.cpp
        Main/Menu.h
        Structures/Matrix.cpp
        Structures/Matrix.h
        Structures/SymmetricMatrix.cpp
        Structures/SymmetricMatrix.h
        Utils/GenerateMatrix.cpp
        Utils/GenerateMatrix.h
        Utils/ReadFile.cpp
        Utils/ReadFile.h)
