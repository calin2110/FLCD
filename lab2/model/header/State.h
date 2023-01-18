//
// Created by popca on 30/11/2022.
//

#pragma once
#include <unordered_set>
#include "LR0Item.h"

class State {
public:
    /*
     * a State consists of multiple, different items, so we will use an unordered set to store them
     * thus adding a LR0Item and checking if a LR0Item exists in a State will be theta(1)
     */
     std::unordered_set<LR0Item> items;
    bool operator==(const State& other) const;
    State(const std::unordered_set<LR0Item>& items);
    State();

    // check whether there are no items in the set of LR0Items
    bool empty() const;
    friend std::ostream &operator<<(std::ostream &os, const State& object);
};

/*
 * implement hash for a State such that we can use unordered sets with State
 * order is NOT important in this case, so we will add all the hash values of the LR0Items
 * (we are required to use a commutative operator, and boost combine is not one of them)
 */
template<>
struct std::hash<State>
{
    std::size_t operator()(State const& state) const noexcept {
        std::size_t seed = 0;
        std::hash<LR0Item> item_hash{};
        for (const LR0Item& item: state.items) {
            seed += item_hash.operator()(item);
        }
        return seed;
    }
};

