//
// Created by popca on 14/12/2022.
//

#pragma once

#include "../../model/header/ParsingNode.h"
#include "../../model/header/Production.h"
#include <list>

#define INVALID_NODE ParsingNode(-1, "", -1, -1)

class SyntaxTree {
private:
    std::list<ParsingNode> parsing_tree;
    std::unordered_set<int> expanded_terminals;
    std::unordered_set<std::string> nonterminals;

public:
    SyntaxTree(const std::string& start_point, std::unordered_set<std::string>  nonterminals);
    ParsingNode find_rightest_terminal();
    void parse_production(const Production& production);
    friend std::ostream &operator<<(std::ostream &os, const SyntaxTree& object);
};