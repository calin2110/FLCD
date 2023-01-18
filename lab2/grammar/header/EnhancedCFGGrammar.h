//
// Created by popca on 30/11/2022.
//

#pragma once
#include <unordered_set>
#include <unordered_map>
#include <list>
#include "../../model/header/Production.h"
#include "Grammar.h"

class EnhancedCFGGrammar {
private:
    std::unordered_set<std::string> nonterminals;
    std::unordered_set<std::string> terminals;
    std::unordered_map<std::string, std::list<Production>> productions;
    std::string start_symbol;

public:
    friend class Parser;
    EnhancedCFGGrammar(const Grammar& grammar);
    std::unordered_set<std::string> get_symbols() const;
};