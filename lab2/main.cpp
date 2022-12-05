#include <iostream>
#include <cassert>
#include "scanner/header/Scanner.h"
#include "exception/LexicalException.h"
#include "finite_automata/header/FiniteAutomata.h"
#include "finite_automata/header/IdentifierFA.h"
#include "finite_automata/header/IntegerConstantFA.h"
#include "test/TestFA.h"
#include "grammar/header/Grammar.h"
#include "parser/header/Parser.h"

void scan() {
    Scanner scanner{};
    try {
        std::string filename_noext = "p3";
        scanner.scan("token.in", "../files/programs/" + filename_noext + ".cln");
        scanner.write_pif_and_symbol_table(
                "../files/output/pif/pif_" + filename_noext + ".out",
                "../files/output/st/st_" + filename_noext + ".out"
        );
        std::cout << "Lexically correct\n";
    } catch (LexicalException &lexicalException) {
        std::cout << "Lexical error\n";
        std::cout << lexicalException.what() << "\n";
    }
}


void finite_automata() {
    FiniteAutomata fa{};
    std::ifstream file("../files/finite_automata/fa.in");
    file >> fa;
    file.close();
    fa.print_states(std::cout);
    fa.print_alphabet(std::cout);
    fa.print_initial_state(std::cout);
    fa.print_final_states(std::cout);
    fa.print_transitions(std::cout);
    fa.is_sequence_accepted("01");
}

void grammar() {
    std::ifstream file("../files/grammar/g2.in");
    Grammar grammar{};
    file >> grammar;
    grammar.print_nonterminals(std::cout);
    grammar.print_terminals(std::cout);
    grammar.print_productions(std::cout);
    grammar.print_start_symbol(std::cout);
    std::cout << grammar.is_grammar_context_free();
}

void parser() {
    std::ifstream file("testg.in");
    Grammar grammar{};
    file >> grammar;
    EnhancedCFGGrammar enhancedCfgGrammar{grammar};

    Parser parser(enhancedCfgGrammar);
    parser.run();
}

int main() {
    parser();
//    grammar();
//    finite_automata();
//    TestFA::test_all();
//    std::cout << " all tests passed\n";
//    finite_automata();
//    scan();
    return 0;
}

