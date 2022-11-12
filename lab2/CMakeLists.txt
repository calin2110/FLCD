cmake_minimum_required(VERSION 3.17)
project(fcld_lab2_final)

set(CMAKE_CXX_STANDARD 17)

add_executable(fcld_lab2_final
        main.cpp
        data_structure/implementation/HashTable.cpp
        data_structure/header/HashTable.h
        scanner/implementation/Scanner.cpp
        scanner/header/Scanner.h
        model/implementation/Token.cpp
        model/header/Token.h
        data_structure/implementation/PIF.cpp
        data_structure/header/PIF.h
        data_structure/implementation/SymbolTable.cpp
        data_structure/header/SymbolTable.h
        finite_automata/header/FiniteAutomata.h
        finite_automata/implementation/FiniteAutomata.cpp
        exception/LexicalException.h
        exception/NotYetImplementedException.h
        exception/FAFormatException.h
        finite_automata/header/IdentifierFA.h
        finite_automata/header/IntegerConstantFA.h
        test/TestFA.h
        )