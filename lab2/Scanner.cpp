//
// Created by popca on 26/10/2022.
//

#include "Scanner.h"
#include <iostream>
#include <regex>

std::unordered_set<std::string> Scanner::get_reserved_words(const std::string &filepath) {
    std::ifstream file(filepath);
    std::string reserved_word;
    std::unordered_set<std::string> res_words{};
    while (file >> reserved_word) {
        res_words.insert(reserved_word);
    }
    file.close();
    return res_words;
}

void Scanner::scan(const std::string &filepath) {
    std::list<std::string> tokens = get_tokens(filepath);
    classify_all_tokens(tokens);
}

Scanner::Scanner(const std::string &reserved_words_filepath) {
    reserved_words = get_reserved_words(reserved_words_filepath);
    symbolTable = SymbolTable();
    pif = PIF();
}

std::list<std::string> Scanner::get_tokens(const std::string &filepath) {
    std::ifstream file(filepath);
    std::string word;
    std::unordered_set<char> separators{
            '(', ')', '{', '}', ':', ';', '[', ']', '+', '-', '*', '/', '=', '<', '>', '&', '|'
    };
    std::unordered_set<char> look_ahead_separators{
            '+', '-', '*', '/', '=', '<', '>', '&', '|'
    };
    std::list<std::string> tokens{};

    while (file >> word) {
        int i = 0, start = 0;
        while (i < word.size()) {
            char current_char = word[i];
            if (separators.find(current_char) != separators.end()) {
                if (start != i) {
                    std::string current_word = word.substr(start, i - start);
                    tokens.emplace_back(current_word);
                }
                if (look_ahead_separators.find(current_char) != look_ahead_separators.end() &&
                    i != word.size() - 1 && reserved_words.find(word.substr(i, 2)) != reserved_words.end()) {
                    std::string current_word = word.substr(i, 2);
                    start = i + 2;
                    i++;
                    tokens.emplace_back(current_word);
                } else {
                    std::string current_word = std::string(1, word[i]);
                    tokens.emplace_back(current_word);
                    start = i + 1;
                }
            }
            i++;
        }
        if (i != start) {
            std::string current_word = word.substr(start, i - start);
            tokens.push_back(current_word);
        }
    }
    return tokens;
}

TokenType Scanner::classify_token(const std::string &token) {
    if (reserved_words.find(token) != reserved_words.end()) {
        return RESERVED_WORD;
    }
    if (is_token_identifier(token)) {
        return IDENTIFIER;
    }
    if (is_token_integer_constant(token)) {
        return INTEGER_CONSTANT;
    }
    if (is_token_boolean_constant(token)) {
        return BOOLEAN_CONSTANT;
    }
    if (is_token_string_constant(token)) {
        return STRING_CONSTANT;
    }
    // TODO: change exception
    throw std::exception();
}

void Scanner::classify_all_tokens(const std::list<std::string> &tokens) {
    for (const std::string &token: tokens) {
        TokenType type = classify_token(token);
        int position;
        std::any value;
        switch (type) {
            case RESERVED_WORD:
                pif.add_token(token, -1);
                break;
            case IDENTIFIER:
                position = symbolTable.add(token);
                pif.add_token("ID", position);
                break;
            case INTEGER_CONSTANT:
                value = std::stoi(token);
                position = symbolTable.add(value);
                pif.add_token("CONST", position);
                break;
            case STRING_CONSTANT:
                position = symbolTable.add(token);
                pif.add_token("CONST", position);
                break;
            case BOOLEAN_CONSTANT:
                value = token == "true";
                position = symbolTable.add(value);
                pif.add_token("CONST", position);
                break;
        }
    }
}

void Scanner::write_pif_and_symbol_table(const std::string &pif_filepath, const std::string &st_filepath) {
    std::ofstream pif_file(pif_filepath);
    pif_file << pif;
    pif_file.close();

    std::ofstream st_file(st_filepath);
    st_file << symbolTable;
    st_file.close();
}
