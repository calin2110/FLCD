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
    std::string start;
    std::deque<std::string> lhs;
    std::deque<std::string> rhs;
    LR0Item(const std::string& start,
            const std::list<std::string>& lhs,
            const std::list<std::string>& rhs);
    LR0Item(const std::string& start,
            const std::deque<std::string>& lhs,
            const std::deque<std::string>& rhs);
    LR0Item shift_dot_right() const;
    bool operator==(const LR0Item& other) const;
    friend struct std::hash<LR0Item>;
    friend std::ostream &operator<<(std::ostream &os, const LR0Item& object);
};

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

