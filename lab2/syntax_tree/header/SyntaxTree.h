//
// Created by popca on 14/12/2022.
//

#pragma once

#include "../../model/header/ParsingNode.h"
#include "../../model/header/Production.h"
#include <list>
#include <stack>

class SyntaxTree {
private:
    std::list<ParsingNode> parsing_tree;
    std::stack<ParsingNode> nonterminal_stack;
    std::unordered_set<std::string> nonterminals;

public:
    SyntaxTree(const std::string& start_point, std::unordered_set<std::string>  nonterminals);
    void parse_production(const Production& production);
    friend std::ostream &operator<<(std::ostream &os, const SyntaxTree& object);
};