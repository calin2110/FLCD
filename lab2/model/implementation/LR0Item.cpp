//
// Created by popca on 30/11/2022.
//

#include "../header/LR0Item.h"

LR0Item::LR0Item(
        const std::string &start,
        const std::list<std::string> &lhs,
        const std::list<std::string> &rhs) {
    this->start = start;
    this->lhs = std::deque<std::string>{};
    for (const std::string& lhs_item: lhs) {
        this->lhs.push_back(lhs_item);
    }
    for (const std::string& rhs_item: rhs) {
        this->rhs.push_back(rhs_item);
    }
}

bool LR0Item::operator==(const LR0Item &other) const {
    if (start != other.start) {
        return false;
    }
    if (lhs.size() != other.lhs.size() || rhs.size() != other.rhs.size()) {
        return false;
    }

    auto other_lhs_iterator = other.lhs.begin();
    for (const std::string& lhs_item: lhs) {
        if (lhs_item != *other_lhs_iterator) {
            return false;
        }
        std::advance(other_lhs_iterator, 1);
    }

    auto other_rhs_iterator = other.rhs.begin();
    for (const std::string& rhs_item: rhs) {
        if (rhs_item != *other_rhs_iterator) {
            return false;
        }
        std::advance(other_rhs_iterator, 1);
    }
    return true;
}

LR0Item LR0Item::shift_dot_right() const{
    std::deque<std::string> current_rhs{};
    current_rhs.insert(current_rhs.end(), rhs.begin(), rhs.end());
    std::string moved_elem = current_rhs.front();
    current_rhs.pop_front();

    std::deque<std::string> current_lhs{};
    current_lhs.insert(current_lhs.end(), lhs.begin(), lhs.end());
    current_lhs.push_back(moved_elem);
    return LR0Item(start, current_lhs, current_rhs);
}

LR0Item::LR0Item(const std::string &start, const std::deque<std::string> &lhs, const std::deque<std::string> &rhs) {
    this->start = start;
    this->lhs = lhs;
    this->rhs = rhs;
}