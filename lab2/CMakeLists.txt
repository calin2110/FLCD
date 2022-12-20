cmake_minimum_required(VERSION 3.16)
project(fcld_lab2_final)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(
        Boost 1.73.0
)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(fcld_lab2_final
        main.cpp
        data_structure/implementation/HashTable.cpp
        data_structure/header/HashTable.h
        scanner/implementation/Scanner.cpp
        scanner/header/Scanner.h
        model/implementation/Token.cpp
        model/header/Token.h
        pif/implementation/PIF.cpp
        pif/header/PIF.h
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
        grammar/implementation/Grammar.cpp
        grammar/header/Grammar.h
        model/header/Production.h
        model/implementation/Production.cpp
        exception/GrammarFormatException.h
        parser/header/Parser.h
        parser/implementation/Parser.cpp
        model/header/LR0Item.h
        model/implementation/LR0Item.cpp
        grammar/header/EnhancedCFGGrammar.h grammar/implementation/EnhancedCFGGrammar.cpp model/header/State.h model/implementation/State.cpp test/TestParser.h model/header/Actions.h model/implementation/Actions.cpp data_structure/header/ActionTable.h data_structure/implementation/ActionTable.cpp syntax_tree/header/SyntaxTree.h syntax_tree/implementation/SyntaxTree.cpp model/header/ParsingNode.h model/implementation/ParsingNode.cpp exception/LR0Exception.h exception/ConflictException.h)