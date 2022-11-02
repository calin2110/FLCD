#include <iostream>
#include "HashTable.h"
#include "Scanner.h"
#include "LexicalException.h"

int main() {
    Scanner scanner{};
    try {
        scanner.scan("token.in", "../programs/p2.cln");
        scanner.write_pif_and_symbol_table("pif2.out", "st2.out");
        std::cout << "Lexically correct\n";
    } catch (LexicalException& lexicalException) {
        std::cout << "Lexical error\n";
        std::cout << lexicalException.what() << "\n";
    }
    return 0;
}