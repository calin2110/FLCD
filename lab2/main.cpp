#include <iostream>
#include "HashTable.h"
#include "Scanner.h"

int main() {
    Scanner scanner{};
    scanner.scan("token.in", "p3.cln");
    scanner.write_pif_and_symbol_table("pif.out", "st.out");
    return 0;
}