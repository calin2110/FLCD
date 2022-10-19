//
// Created by popca on 19/10/2022.
//

#include "SymbolTable.h"

#include <iostream>

SymbolTable::SymbolTable() {
    quotient = 647;
    this->current_position = 0;
    this->hash_table = new Node*[quotient];
    for (int i = 0; i < quotient; i++) {
        this->hash_table[i] = nullptr;
    }
}

Node *SymbolTable::add(const std::any& symbol) {
    Node *searched_node = search(symbol);
    if (searched_node != nullptr) {
        return searched_node;
    }

    Node* added_node = new Node;
    unsigned int hash_value = hash(symbol);
    added_node->position = current_position;
    added_node->symbol = symbol;
    added_node->next = this->hash_table[hash_value];
    this->current_position++;
    this->hash_table[hash_value] = added_node;
    return added_node;
}

Node *SymbolTable::search(const std::any& symbol) const {
    unsigned int hash_value = hash(symbol);
    Node* current_node = this->hash_table[hash_value];
    while (current_node != nullptr) {
        if (symbols_are_equal(current_node->symbol, symbol)) {
            return current_node;
        }
        current_node = current_node->next;
    }
    return nullptr;
}

unsigned int SymbolTable::hash(const std::any &symbol) const {
    if (symbol.type() == typeid(const char*)) {
        return hash_string(std::any_cast<const char*>(symbol));
    }
    if (symbol.type() == typeid(int)) {
        return hash_int(std::any_cast<int>(symbol));
    }
    if (symbol.type() == typeid(bool)) {
        return hash_boolean(std::any_cast<bool>(symbol));
    }
    return -1;
}


SymbolTable::~SymbolTable() {
    for (int i = 0; i < quotient; i++) {
        Node* current_node = this->hash_table[i];
        while (current_node != nullptr) {
            Node* next_node = current_node->next;
            delete current_node;
            current_node = next_node;
        }
    }
    delete[] hash_table;
}

unsigned int SymbolTable::hash_int(const int symbol) const {
    return symbol % quotient;
}

unsigned int SymbolTable::hash_boolean(const bool symbol) const {
    return symbol % quotient;
}

unsigned int SymbolTable::hash_string(const std::string &symbol) const {
    unsigned int ascii_sum = 0;
    for (char character: symbol) {
        ascii_sum += character;
    }
    return ascii_sum % quotient;
}

bool symbols_are_equal(const std::any &symbol1, const std::any &symbol2) {
    if (symbol1.type() != symbol2.type()) {
        return false;
    }
    if (symbol1.type() == typeid(int)) {
        return std::any_cast<int>(symbol1) == std::any_cast<int>(symbol2);
    }
    if (symbol1.type() == typeid(const char*)) {
        return std::string(std::any_cast<const char*>(symbol1)) ==
            std::string(std::any_cast<const char*>(symbol2));
    }
    if (symbol1.type() == typeid(bool)) {
        return std::any_cast<bool>(symbol1) == std::any_cast<bool>(symbol2);
    }
    return false;
}
