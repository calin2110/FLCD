//
// Created by popca on 19/10/2022.
//

#include "HashTable.h"
#include <stdexcept>
#include <string>
#include <iostream>

HashTable::HashTable(int quotient, double max_load_factor) {
    this->quotient = quotient;
    this->current_position = 0;
    this->initialise_hash_table();
    this->size = 0;
    this->max_load_factor = max_load_factor;
}

Node *HashTable::add(const std::any& symbol) {
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

Node *HashTable::search(const std::any& symbol) const {
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

unsigned int HashTable::hash(const std::any &symbol) const {
    if (symbol.type() == typeid(std::string)) {
        unsigned int ascii_sum = 0;
        for (char character: std::any_cast<std::string>(symbol)) {
            ascii_sum += character;
        }
        return ascii_sum % quotient;
    }
    if (symbol.type() == typeid(int)) {
        return std::any_cast<int>(symbol) % quotient;
    }
    if (symbol.type() == typeid(bool)) {
        return std::any_cast<bool>(symbol) % quotient;
    }
    throw std::invalid_argument("Invalid type to add in the symbol table!");
}

HashTable::~HashTable() {
    for (int i = 0; i < quotient; i++) {
        Node *current_node = this->hash_table[i];
        while (current_node != nullptr) {
            Node *next_node = current_node->next;
            delete current_node;
            current_node = next_node;
        }
    }
    delete[] hash_table;
}

void HashTable::resize() {
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

void HashTable::initialise_hash_table() {
    this->hash_table = new Node*[quotient];
    for (int i = 0; i < quotient; i++) {
        this->hash_table[i] = nullptr;
    }
}

std::ostream &operator<<(std::ostream &os, HashTable &hashTable) {
    for (int i = 0; i < hashTable.quotient; i++) {
        Node* current_node = hashTable.hash_table[i];
        while (current_node != nullptr) {
            const std::any symbol = current_node->symbol;
            if (symbol.type() == typeid(int)) {
                os << std::any_cast<int>(symbol);
            }
            if (symbol.type() == typeid(bool)) {
                os << (std::any_cast<bool>(symbol) ? "true" : "false");
            }
            if (symbol.type() == typeid(std::string)) {
                os << std::any_cast<std::string>(symbol);
            }
            os << " " << current_node->position << "\n";
            current_node = current_node->next;
        }
    }
    return os;
}

//HashTable::HashTable(HashTable &table) {
//    this->quotient = table.quotient;
//    this->current_position = table.current_position;
//    this->size = table.size;
//    this->max_load_factor = table.max_load_factor;
//    this->initialise_hash_table();
//    for (int i = 0; i < table.quotient; i++) {
//        Node* current_node = table.hash_table[i];
//        Node* previous_node = nullptr;
//        while (current_node != nullptr) {
//            Node* created_node = new Node;
//            if (previous_node != nullptr) {
//                previous_node->next = created_node;
//            } else {
//                hash_table[i] = created_node;
//            }
//            created_node->next = nullptr;
//            created_node->symbol = current_node->symbol;
//            created_node->position = current_node->position;
//            previous_node = created_node;
//            current_node = current_node->next;
//        }
//    }
//}

HashTable &HashTable::operator=(const HashTable &table) {
    if (&table == this) {
        return *this;
    }
    this->quotient = table.quotient;
    this->current_position = table.current_position;
    this->size = table.size;
    this->max_load_factor = table.max_load_factor;
    this->initialise_hash_table();
    for (int i = 0; i < table.quotient; i++) {
        Node* current_node = table.hash_table[i];
        Node* previous_node = nullptr;
        while (current_node != nullptr) {
            Node* created_node = new Node;
            if (previous_node != nullptr) {
                previous_node->next = created_node;
            } else {
                hash_table[i] = created_node;
            }
            created_node->next = nullptr;
            created_node->symbol = current_node->symbol;
            created_node->position = current_node->position;
            previous_node = created_node;
            current_node = current_node->next;
        }
    }
    return *this;
}

bool symbols_are_equal(const std::any &symbol1, const std::any &symbol2) {
    if (symbol1.type() != symbol2.type()) {
        return false;
    }
    if (symbol1.type() == typeid(int)) {
        return std::any_cast<int>(symbol1) == std::any_cast<int>(symbol2);
    }
    if (symbol1.type() == typeid(bool)) {
        return std::any_cast<bool>(symbol1) == std::any_cast<bool>(symbol2);
    }
    if (symbol1.type() == typeid(std::string)) {
        return std::any_cast<std::string>(symbol1)
                    == std::any_cast<std::string>(symbol2);
    }
    throw std::invalid_argument("Invalid type to check the equality for!");
}
