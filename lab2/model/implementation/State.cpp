//
// Created by popca on 30/11/2022.
//

#include "../header/State.h"

bool State::operator==(const State &other) const {
    if (items.size() != other.items.size()) {
        return false;
    }
    for (const LR0Item& item: items) {
        if (other.items.find(item) == other.items.end()) {
            return false;
        }
    }
    return true;
}

State::State(const std::unordered_set<LR0Item>& items) {
    this->items = items;
}

bool State::empty() const {
    return items.empty();
}

std::ostream &operator<<(std::ostream &os, const State &object) {
    os << "State: ";
    for (const LR0Item& item: object.items) {
        os << item << " ";
    }
    os << "\n";
    return os;
}

State::State() {

}
