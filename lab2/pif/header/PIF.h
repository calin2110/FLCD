//
// Created by popca on 26/10/2022.
//

#pragma once
#include <list>
#include <fstream>
#include "../../model/header/Token.h"

class PIF {
private:
    /*
     * PIF uses the data structure of a std::list because the tokens need to be added in order they are found
     * so a linked list would be the most efficient, as adding to the end of a linked list is a O(1) operation
     * and luckily, in CPP, std::list is implemented as a linked list
     */
    std::list<Token> tokens;

public:
    PIF();
    std::list<Token> get_tokens() const;
    void add_token(const std::string& name, const int position);
    friend std::ostream &operator<<(std::ostream &os, const PIF& pif);
};


