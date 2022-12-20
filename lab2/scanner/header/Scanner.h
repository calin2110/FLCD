//
// Created by popca on 26/10/2022.
//

#pragma once
#include <unordered_set>
#include <string>
#include "../../model/header/Token.h"
#include "../../pif/header/PIF.h"
#include "../../data_structure/header/SymbolTable.h"
#include <list>

class Scanner {
private:
    std::unordered_set<std::string> reserved_words;
    std::unordered_set<char> separators;
    std::unordered_set<char> look_ahead_separators;

public:
    std::pair<PIF, SymbolTable> scan(const std::string& code_filepath);
    void write_pif_and_symbol_table(
            const std::string& pif_filepath,
            const PIF& pif,
            const std::string& st_filepath,
            const SymbolTable& st
    );
    Scanner(
        std::unordered_set<std::string> reserved_words,
        std::unordered_set<char> separators,
        std::unordered_set<char> look_ahead_separators
    );

private:
    std::list<std::string> get_tokens(const std::string &filepath);
    TokenType classify_token(const std::string& token);
    void classify_all_tokens(
            const std::list<std::string>& tokens,
            PIF& pif,
            SymbolTable& symbolTable
    );
};
