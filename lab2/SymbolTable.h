//
// Created by popca on 26/10/2022.
//

#pragma once
#include "HashTable.h"
#include <fstream>

class SymbolTable {
private:

    HashTable table;

public:
    SymbolTable();
    int add(const std::any& symbol);
    friend std::ostream &operator<<(std::ostream &os, SymbolTable& object);
};


