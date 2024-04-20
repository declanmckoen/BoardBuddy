cmake_minimum_required(VERSION 3.25)
project(BoardBuddy)

set(CMAKE_CXX_STANDARD 17)

add_executable(BoardBuddy src/main.cpp
        src/ChessGame.h
        src/ChessGame.cpp
        src/DataReader.cpp
        src/DataReader.h
        src/Interface.h
        src/MergeSort.h
        src/QuickSort.h)
