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
    // parsing tree should be a list, as adding to the end should be theta(1)
    std::list<ParsingNode> parsing_tree;

    /*
     * we use an additional nonterminal stack in order to make finding the right-most
     * nonterminal theta(1)
     * when we transform a production into multiple symbols, we add the nonterminals to this stack in
     * the order we find them
     */
    std::stack<ParsingNode> nonterminal_stack;

    // we need the set of nonterminals so that checking whether a symbol is terminal or nonterminal is theta(1)
    std::unordered_set<std::string> nonterminals;

public:
    SyntaxTree(const std::string& start_point, std::unordered_set<std::string>  nonterminals);

    // given a production, we parse it by expanding it
    void parse_production(const Production& production);

    friend std::ostream &operator<<(std::ostream &os, const SyntaxTree& object);
};