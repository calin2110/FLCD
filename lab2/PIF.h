//
// Created by popca on 26/10/2022.
//

#pragma once
#include <list>
#include <fstream>
#include "Token.h"

class PIF {
private:
    std::list<Token> tokens;

public:
    PIF();

    void add_token(const std::string& name, const int position);
    friend std::ostream &operator<<(std::ostream &os, PIF& pif);
};


