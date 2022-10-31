//
// Created by popca on 26/10/2022.
//

#include "Token.h"
#include <regex>

bool is_token_identifier(const std::string& token) {
    /*
     * This regex represents:
     * line starting with a letter (lower case or upper case) or underline
     * followed by a character which is either letter (lower case or upper case), underline or digit
     * 0 or more times and then the end of the line
     */
    std::regex regex{"^[A-Z|a-z|_][A-Z|a-z|_|0-9]*$"};
    return std::regex_match(token, regex);
}

bool is_token_integer_constant(const std::string& token) {
    /*
     * This regex represents:
     * line starting with 0 and then end of line
     * or line starting with + or - or nothing, then a non-zero digit
     * followed by a digit 0 or more times and then the end of the line
     */
    std::regex regex{"^(0|^[+|-]{0,1}[1-9][0-9]*)$"};
    return std::regex_match(token, regex);
}

bool is_token_string_constant(const std::string& token) {
    /*
     * This regex represents:
     * line starting with ", then either ~ ! @ # $ ^ , . ? _ or any letter (lower case or upper case) or any digit
     * 0 or more times, then another " and then the end of the line
     */
    std::regex regex{"^\"[~|!|@|#|$|^|,|.|?|_|A-Z|a-z|0-9]*\"$"};
    return std::regex_match(token, regex);
}

bool is_token_boolean_constant(const std::string& token) {
    /*
     * A boolean constant can be either true or false, so we do not need any regex there
     */
    return token == "true" || token == "false";
}

Token::Token(const std::string &name, const int position) {
    this->name = name;
    this->position = position;
}
