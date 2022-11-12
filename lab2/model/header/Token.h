//
// Created by popca on 26/10/2022.
//

#pragma once
#include <string>

enum TokenType {
    RESERVED_WORD,
    IDENTIFIER,
    INTEGER_CONSTANT,
    STRING_CONSTANT,
    BOOLEAN_CONSTANT
};

class Token {
public:
    Token(const std::string& name, const int& position);
    std::string name;
    int position;
};

bool is_token_identifier(const std::string& token);
bool is_token_integer_constant(const std::string& token);
bool is_token_string_constant(const std::string& token);
bool is_token_boolean_constant(const std::string& token);

