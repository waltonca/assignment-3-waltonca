cmake_minimum_required(VERSION 3.17)
project(Assignment_3)

set(CMAKE_CXX_STANDARD 23)

add_executable(spellcheck
        src/main.cpp
        src/application.h
        src/application.cpp
        src/utility.h
        src/utility.cpp
        src/BST.h
        src/BST.cpp)
