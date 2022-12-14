//
// Created by popca on 26/10/2022.
//

#include "../header/SymbolTable.h"

int SymbolTable::add(const std::any &symbol) {
    return table.add(symbol)->position;
}

std::ostream &operator<<(std::ostream &os, const SymbolTable &symbolTable) {
    os << symbolTable.table;
    return os;
}

SymbolTable::SymbolTable(): table(647, 0.75) {

}

SymbolTable &SymbolTable::operator=(const SymbolTable &other) {
    if (&other == this) {
        return *this;
    }
    table = other.table;
    return *this;
}
