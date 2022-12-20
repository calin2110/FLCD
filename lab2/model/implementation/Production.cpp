//
// Created by popca on 23/11/2022.
//

#include "../header/Production.h"
#include "../../exception/GrammarFormatException.h"

#include <utility>

Production::Production(
        std::list<std::string> lhs,
        std::list<std::string> rhs
) : lhs(std::move(lhs)), rhs(std::move(rhs)) {

}

Production Production::read_from_line(
        const std::string &line,
        std::unordered_set<std::string> terminals,
        std::unordered_set<std::string> nonterminals
) {
    {
        std::istringstream iss(line);
        std::string word;
        bool is_lhs = true;
        std::list<std::string> lhs{};
        std::list<std::string> rhs{};
        while (iss >> word) {
            if (word.size() == 2 && word[0] == '-' && word[1] == '>') {
                if (!is_lhs) {
                    throw GrammarFormatException("Double arrows found which is invalid!");
                }
                is_lhs = false;
            } else {
                if (terminals.find(word) == terminals.end() &&
                        nonterminals.find(word) == terminals.end()) {
                    throw GrammarFormatException("We cannot find " + word +
                                " in either terminal set or terminal set!");
                }
                if (is_lhs) {
                    lhs.push_back(word);
                } else {
                    rhs.push_back(word);
                }
            }
        }
        if (rhs.empty()) {
            // EPSILON
            rhs.emplace_back("");
        }
        return Production(lhs, rhs);
    }
}

std::ostream &operator<<(std::ostream &os, Production &object) {
    for (const std::string& lhs_item: object.lhs) {
        os << lhs_item << " ";
    }
    os << "-> ";
    for (const std::string& rhs_item: object.rhs) {
        os << (rhs_item.empty() ? "\u03B5" : rhs_item) << " ";
    }
    os << "\n";
    return os;
}