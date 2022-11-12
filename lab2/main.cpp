#include <iostream>
#include <cassert>
#include "scanner/header/Scanner.h"
#include "exception/LexicalException.h"
#include "finite_automata/header/FiniteAutomata.h"
#include "finite_automata/header/IdentifierFA.h"
#include "finite_automata/header/IntegerConstantFA.h"
#include "test/TestFA.h"

void scan() {
    Scanner scanner{};
    try {
        std::string filename_noext = "p1err"    ;
        scanner.scan("token.in", "../programs/" + filename_noext + ".cln");
        scanner.write_pif_and_symbol_table(
                "../output/pif/pif_" + filename_noext + ".out",
                "../output/st/st_" + filename_noext + ".out"
        );
        std::cout << "Lexically correct\n";
    } catch (LexicalException& lexicalException) {
        std::cout << "Lexical error\n";
        std::cout << lexicalException.what() << "\n";
    }
}


void finite_automata() {
    FiniteAutomata fa{};
    std::ifstream file("fa.in");
    file >> fa;
    file.close();
    fa.print_states(std::cout);
    fa.print_alphabet(std::cout);
    fa.print_initial_state(std::cout);
    fa.print_final_states(std::cout);
    fa.print_transitions(std::cout);
    fa.is_sequence_accepted("01");
}

int main() {
//    finite_automata();
    TestFA::test_all();
    finite_automata();
    return 0;
}

