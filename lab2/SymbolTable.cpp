//
// Created by popca on 19/10/2022.
//

#include "SymbolTable.h"
#include <stdexcept>
#include <string>
#include <iostream>

SymbolTable::SymbolTable(int quotient, double max_load_factor) {
    this->quotient = quotient;
    this->current_position = 0;
    this->initialise_hash_table();
    this->size = 0;
    this->max_load_factor = max_load_factor;
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
    this->size++;

    if (((double) this->size) / this->quotient > max_load_factor) {
        this->resize();
    }

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
        unsigned int ascii_sum = 0;
        for (char character: std::string(std::any_cast<const char*>(symbol))) {
            ascii_sum += character;
        }
        std::cout << std::string(std::any_cast<const char*>(symbol)) << " has the hash value " << ascii_sum % quotient << "\n";
        return ascii_sum % quotient;
    }
    if (symbol.type() == typeid(int)) {
        std::cout << std::any_cast<int>(symbol) << " has the hash value " << std::any_cast<int>(symbol) % quotient << "\n";
        return std::any_cast<int>(symbol) % quotient;
    }
    if (symbol.type() == typeid(bool)) {
        std::cout << std::any_cast<bool>(symbol) << " has the hash value " << std::any_cast<bool>(symbol) % quotient << "\n";
        return std::any_cast<bool>(symbol) % quotient;
    }
    throw std::invalid_argument("Invalid type to add in the symbol table!");
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

void SymbolTable::resize() {
    std::cout << " we resizing man " << this->quotient << "\n";
    Node** saved_hash_table = this->hash_table;
    int saved_quotient = this->quotient;
    this->quotient *= 2;
    this->initialise_hash_table();
    for (int i = 0; i < saved_quotient; i++) {
        Node* current_node = saved_hash_table[i];
        while (current_node != nullptr) {
            Node* saved_next_node = current_node->next;

            unsigned int hash_value = hash(current_node->symbol);
            current_node->next = this->hash_table[hash_value];
            this->hash_table[hash_value] = current_node;

            current_node = saved_next_node;
        }
    }

    delete[] saved_hash_table;
}

void SymbolTable::initialise_hash_table() {
    this->hash_table = new Node*[quotient];
    for (int i = 0; i < quotient; i++) {
        this->hash_table[i] = nullptr;
    }
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
    throw std::invalid_argument("Invalid type to check the equality for!");
}
