//
// Created by popca on 14/12/2022.
//

#pragma once
#include <string>
#include <iostream>

class ParsingNode {
public:
    ParsingNode(int index, std::string value, int parent_index, int left_sibling_index);
    bool operator==(const ParsingNode& other) const;
    friend std::ostream &operator<<(std::ostream &os, const ParsingNode& object);

public:
    int index;
    std::string value;
    int parent_index;
    int left_sibling_index;

};