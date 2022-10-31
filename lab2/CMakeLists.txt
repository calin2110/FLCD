cmake_minimum_required(VERSION 3.16)
project(fcld_lab2_final)

set(CMAKE_CXX_STANDARD 17)

add_executable(fcld_lab2_final
        main.cpp
        HashTable.cpp
        HashTable.h
        Scanner.cpp
        Scanner.h
        Token.cpp
        Token.h
        PIF.cpp
        PIF.h
        SymbolTable.cpp
        SymbolTable.h
        LexicalException.h
)