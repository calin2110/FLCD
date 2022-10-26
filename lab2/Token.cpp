//
// Created by popca on 26/10/2022.
//

#include "Token.h"
#include <regex>

bool is_token_identifier(const std::string& token) {
    std::regex regex{"^[A-Z|a-z|_][A-Z|a-z|_|0-9]*$"};
    return std::regex_match(token, regex);
}

bool is_token_integer_constant(const std::string& token) {
    std::regex regex{"^(0|^[+|-]{0,1}[1-9][0-9]*)$"};
    return std::regex_match(token, regex);
}

bool is_token_string_constant(const std::string& token) {
    std::regex regex{"^\"[~|!|@|#|$|^|,|.|?|_|A-Z|a-z|0-9]*\"$"};
    return std::regex_match(token, regex);
}

bool is_token_boolean_constant(const std::string& token) {
    return token == "true" || token == "false";
}

Token::Token(const std::string &name, const int position) {
    this->name = name;
    this->position = position;
}
