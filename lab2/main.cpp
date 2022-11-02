#include <iostream>
#include "HashTable.h"
#include "Scanner.h"
#include "LexicalException.h"

int main() {
    Scanner scanner{};
    try {
        std::string filename_noext = "p1err";
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
    return 0;
}