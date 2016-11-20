cmake_minimum_required(VERSION 3.3)
project(SistFicheros)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Arbol.cpp
    Arbol.h
    Disco.cpp
    Disco.h
    main.cpp
    Nodo.cpp
    Nodo.h
    Terminal.cpp
    Terminal.h)

add_executable(SistFicheros ${SOURCE_FILES})