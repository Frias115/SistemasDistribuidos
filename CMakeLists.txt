project(SistemasDistribuidos)

set(CMAKE_C_COMPILER "mpicc")
set(CMAKE_CXX_COMPILER "mpiCC")
set(CMAKE_VERBOSE_MAKEFILE "true")
set(CMAKE_INCLUDE_PATH "/usr/include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

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

add_executable(SistemasDistribuidos ${SOURCE_FILES})