cmake_minimum_required(VERSION 3.7)
project(LR_0)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(LR_0
        AnalysisTable.cpp
        AnalysisTable.h
        DFA.cpp
        DFA.h
        Grammar.cpp
        Grammar.h
        Item.cpp
        Item.h
        main.cpp
        Status.cpp
        Status.h)
