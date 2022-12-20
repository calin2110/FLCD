//
// Created by popca on 26/10/2022.
//

#pragma once
#include <fstream>
#include "HashTable.h"

class SymbolTable {
private:

    HashTable table;

public:
    SymbolTable& operator=(const SymbolTable& other);
    SymbolTable();
    int add(const std::any& symbol);
    friend std::ostream &operator<<(std::ostream &os, const SymbolTable& object);
};


