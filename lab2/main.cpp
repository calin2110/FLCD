#include <iostream>
#include "HashTable.h"
#include "Scanner.h"

int main() {
    Scanner scanner{"token.in"};
    scanner.scan("p3.cln");
    scanner.write_pif_and_symbol_table("pif1.out", "st1.out");
    return 0;
}