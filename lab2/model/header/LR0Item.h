//
// Created by popca on 30/11/2022.
//

#pragma once
#include <deque>
#include <string>
#include <list>
#include <iostream>
#include <boost/functional/hash.hpp>

class LR0Item {
public:
    // string representing the left side of the item and the start at the same time
    std::string start;

    /*
     * deque representing the left side of the right hand side of the item, thus the part before the dot
     * we are using a deque so that popping from the end is theta(1) when shifting
     */
    std::deque<std::string> lhs;

    /*
     * deque representing the right side of the right hand side of the item, thus the part after the dot
     * we are using a deque so that adding to the beginning is theta(1) when shifting
     */
    std::deque<std::string> rhs;

    LR0Item(const std::string& start,
            const std::list<std::string>& lhs,
            const std::list<std::string>& rhs);

    LR0Item(const std::string& start,
            const std::deque<std::string>& lhs,
            const std::deque<std::string>& rhs);

    /*
     * we create a new LR0Item by copying the current lhs and rhs, but
     * we move the dot once to the right (pop the last element from lhs and add it to the beginning of the rhs)
     */
    LR0Item shift_dot_right() const;

    bool operator==(const LR0Item& other) const;
    friend struct std::hash<LR0Item>;
    friend std::ostream &operator<<(std::ostream &os, const LR0Item& object);
};

/*
 * implement hash for a LR0Item such that we can use unordered sets with LR0Items
 * order is important in this case, so we can use hash combine from the boost library
 * for hashing, we take each value from the lhs and rhs
 */
template<>
struct std::hash<LR0Item>
{
    std::size_t operator()(LR0Item const& item) const noexcept {
        std::size_t seed = 0;
        boost::hash_combine(seed, item.start);
        for (const std::string& lhs_item: item.lhs) {
            boost::hash_combine(seed, lhs_item);
        }
        for (const std::string& rhs_item: item.rhs) {
            boost::hash_combine(seed, rhs_item);
        }
        return seed;
    }
};

