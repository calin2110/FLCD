//
// Created by popca on 30/11/2022.
//

#pragma once
#include <unordered_set>
#include "../../model/header/LR0Item.h"
#include "../../grammar/header/Grammar.h"
#include "../../grammar/header/EnhancedCFGGrammar.h"
#include "../../model/header/State.h"


class Parser {
private:
    EnhancedCFGGrammar grammar;
    std::unordered_set<LR0Item> create_closure_LR0(const std::unordered_set<LR0Item>& analysis_items);
    State create_goto_LR0(const State& state, const std::string& element);
    std::unordered_set<State> create_col_can_LR0();

public:
    friend class TestParser;
    Parser(EnhancedCFGGrammar grammar);
    void run();
};
