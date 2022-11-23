//
// Created by popca on 23/11/2022.
//

#pragma once
#include <unordered_set>
#include <string>
#include <list>
#include "../../model/header/Production.h"

class Grammar {
private:
    std::unordered_set<std::string> nonterminals;
    std::unordered_set<std::string> terminals;
    std::list<Production> productions;
    std::string start_symbol;

public:
    friend std::istream &operator>>(std::istream &is, Grammar& grammar);

    void print_nonterminals(std::ostream& ostream);
    void print_terminals(std::ostream& ostream);
    void print_productions(std::ostream& ostream);
    void print_start_symbol(std::ostream& ostream);
    bool is_grammar_context_free();
};


