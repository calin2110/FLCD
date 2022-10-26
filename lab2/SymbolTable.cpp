//
// Created by popca on 26/10/2022.
//

#include "SymbolTable.h"

int SymbolTable::add(const std::any &symbol) {
    return table.add(symbol)->position;
}

std::ostream &operator<<(std::ostream &os, SymbolTable &symbolTable) {
    os << symbolTable.table;
    return os;
}
