//
// Created by popca on 30/11/2022.
//

#pragma once
#include <unordered_set>
#include "../../model/header/LR0Item.h"
#include "../../grammar/header/Grammar.h"
#include "../../grammar/header/EnhancedCFGGrammar.h"
#include "../../model/header/State.h"
#include "../../data_structure/header/ActionTable.h"
#include "../../syntax_tree/header/SyntaxTree.h"
#include <queue>

class Parser {
private:
    EnhancedCFGGrammar grammar;
    std::unordered_set<LR0Item> create_closure_LR0(const std::unordered_set<LR0Item>& analysis_items);
    State create_goto_LR0(const State& state, const std::string& element);
    std::pair<std::unordered_set<State>, ActionTable> create_col_can_LR0();
    std::list<Production> run_algorithm(std::deque<std::string>& input_queue, ActionTable& action_table);

public:
    friend class TestParser;
    Parser(EnhancedCFGGrammar grammar);
    SyntaxTree run(std::deque<std::string>& input_queue);
};
