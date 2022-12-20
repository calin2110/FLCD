//
// Created by popca on 14/12/2022.
//

#include "../header/SyntaxTree.h"

#include <utility>

ParsingNode SyntaxTree::find_rightest_terminal() {
    for (auto it = parsing_tree.rbegin(); it != parsing_tree.rend(); it++) {
        if (nonterminals.find(it->value) != nonterminals.end() && expanded_terminals.find(it->index) == expanded_terminals.end()) {
            return *it;
        }
    }
    return INVALID_NODE;
}

void SyntaxTree::parse_production(const Production& production) {
    ParsingNode last = find_rightest_terminal();
    if (last == INVALID_NODE) {
        throw std::invalid_argument("no more terminals");
    }

    int sibling_index = -1;
    for (const std::string& element: production.rhs) {
        ParsingNode new_node{(int) parsing_tree.size() + 1, element, last.index, sibling_index};
        parsing_tree.push_back(new_node);
        sibling_index = new_node.index;
    }
    expanded_terminals.insert(last.index);
}

SyntaxTree::SyntaxTree(const std::string &start_point, std::unordered_set<std::string> nonterminals): nonterminals(std::move(nonterminals)) {
    parsing_tree.emplace_back(parsing_tree.size() + 1, start_point, -1, -1);
}

std::ostream &operator<<(std::ostream &os, const SyntaxTree &object) {
    for (const ParsingNode& node: object.parsing_tree) {
        os << node;
    }
    return os;
}
