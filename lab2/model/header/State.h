//
// Created by popca on 30/11/2022.
//

#pragma once
#include <unordered_set>
#include "LR0Item.h"

class State {
public:
    std::unordered_set<LR0Item> items;
    bool operator==(const State& other) const;
    State(const std::unordered_set<LR0Item>& items);
    State();
    bool empty() const;
    friend std::ostream &operator<<(std::ostream &os, const State& object);
};

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

