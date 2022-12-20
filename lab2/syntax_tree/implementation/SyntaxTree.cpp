//
// Created by popca on 14/12/2022.
//

#include "../header/SyntaxTree.h"

#include <utility>

void SyntaxTree::parse_production(const Production& production) {
    if (nonterminal_stack.empty()) {
        throw std::invalid_argument("no more terminals");
    }
    ParsingNode last_nonterminal = nonterminal_stack.top();
    nonterminal_stack.pop();

    int sibling_index = -1;
    for (const std::string& element: production.rhs) {
        ParsingNode new_node{(int) parsing_tree.size() + 1, element, last_nonterminal.index, sibling_index};
        parsing_tree.push_back(new_node);
        if (nonterminals.find(element) != nonterminals.end()) {
            nonterminal_stack.push(new_node);
        }
        sibling_index = new_node.index;
    }
}

SyntaxTree::SyntaxTree(const std::string &start_point, std::unordered_set<std::string> nonterminals): nonterminals(std::move(nonterminals)) {
    nonterminal_stack = std::stack<ParsingNode>{};
    ParsingNode starting_node{(int) parsing_tree.size() + 1, start_point, -1, -1};
    nonterminal_stack.push(starting_node);
    parsing_tree.push_back(starting_node);
}

std::ostream &operator<<(std::ostream &os, const SyntaxTree &object) {
    for (const ParsingNode& node: object.parsing_tree) {
        os << node;
    }
    return os;
}
