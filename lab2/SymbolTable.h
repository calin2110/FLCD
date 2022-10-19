//
// Created by popca on 19/10/2022.
//

// 1 a

#pragma once
#include <string>
#include <any>

typedef struct Node {
    std::any symbol;
    int position;
    Node* next;
} Node;

class SymbolTable {
private:
    int quotient;
    Node** hash_table;
    int current_position;

public:
    SymbolTable();
    Node* add(const std::any& symbol);
    Node* search(const std::any& symbol) const;
    ~SymbolTable();

private:
    unsigned int hash(const std::any& symbol) const;
    unsigned int hash_int(const int symbol) const;
    unsigned int hash_boolean(const bool symbol) const;
    unsigned int hash_string(const std::string& symbol) const;

};

bool symbols_are_equal(const std::any& symbol1, const std::any& symbol2);
