//
// Created by popca on 26/10/2022.
//

#pragma once
#include <unordered_set>
#include <string>
#include "../../model/header/Token.h"
#include "../../data_structure/header/PIF.h"
#include "../../data_structure/header/SymbolTable.h"
#include <list>

class Scanner {
private:
    std::unordered_set<std::string> reserved_words;
    SymbolTable symbolTable;
    PIF pif;

public:
    std::unordered_set<std::string> get_reserved_words(const std::string& filepath);
    void scan(const std::string& reserved_words_filepath,
              const std::string& code_filepath);
    void write_pif_and_symbol_table(const std::string& pif_filepath,
                               const std::string& st_filepath);
    Scanner();

private:
    std::list<std::string> get_tokens(const std::string &filepath);
    TokenType classify_token(const std::string& token);
    void classify_all_tokens(const std::list<std::string>& tokens);
};
