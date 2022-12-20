//
// Created by popca on 26/10/2022.
//

#include "../header/PIF.h"
#include <fstream>

PIF::PIF() {
    tokens = std::list<Token>();
}

void PIF::add_token(const std::string& name, const int position) {
    tokens.emplace_back(name, position);
}

std::ostream &operator<<(std::ostream &os, const PIF &pif) {
    for (Token const &token: pif.tokens) {
        os << token.name << " " << token.position << "\n";
    }
    return os;
}

std::list<Token> PIF::get_tokens() const {
    return tokens;
}
