//
// Created by popca on 14/12/2022.
//

#include <string>
#include <utility>
#include "../header/ParsingNode.h"


ParsingNode::ParsingNode(int index, std::string value, int parent_index, int left_sibling_index):
    value(std::move(value)), index(index), parent_index(parent_index), left_sibling_index(left_sibling_index) {

}

bool ParsingNode::operator==(const ParsingNode &other) const {
    return index == other.index;
}

std::ostream &operator<<(std::ostream &os, const ParsingNode &object) {
    os << object.index << " " << object.value << " " << object.parent_index << " " << object.left_sibling_index << "\n";
    return os;
}
