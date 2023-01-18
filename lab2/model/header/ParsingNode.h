//
// Created by popca on 14/12/2022.
//

#pragma once
#include <string>
#include <iostream>

/*
 * represents an entry in the SyntaxTree
 * contains the following:
 *          index, int representing its position in the table
 *          value, string representing the symbol it was expanded to
 *          parent_index, int representing the index of the parent or -1 if it is a root node
 *          left_sibling_index, int representing the index of its left sibling or -1 if it has no left siblings
 */
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