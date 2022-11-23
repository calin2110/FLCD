//
// Created by popca on 23/11/2022.
//

#pragma once
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_set>

class Production {
public:
    const std::list<std::string> lhs;
    const std::list<std::string> rhs;
    Production(std::list<std::string> lhs, std::list<std::string> rhs);
    static Production read_from_line(
            const std::string& line,
            std::unordered_set<std::string> terminals,
            std::unordered_set<std::string> nonterminals
    );
    friend std::ostream &operator<<(std::ostream &os, Production& object);
};


