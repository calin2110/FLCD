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
    // each parser requires a CFG grammar which needs to be enhanced
    EnhancedCFGGrammar grammar;

    /*
     * a closure is an unordered set of LR0Items, that is a closure should not contain
     * two identical LR0Items
     * the analysis items, similarly, is an unordered set of LR0Items
     */
    std::unordered_set<LR0Item> create_closure_LR0(const std::unordered_set<LR0Item>& analysis_items);

    // given a state and a symbol, we find the state where it goes to
    State create_goto_LR0(const State& state, const std::string& element);

    /*
     * we create the canonical collection, that is an unordered set of States
     * as it should not contain two identical States
     * while creating the canonical collection, we construct the goto table for efficiency
     */
    std::pair<std::unordered_set<State>, ActionTable> create_col_can_LR0();

    /*
     * we run the algorithm using an input as deque
     * result should be a list because we need adding to the end to be theta(1)
     * input should be a deque because we always take the first character to process it
     * and sometimes we need to add something in front of the queue
     */
    std::list<Production> run_algorithm(std::deque<std::string>& input_queue, ActionTable& action_table);

public:
    friend class TestParser;
    Parser(EnhancedCFGGrammar grammar);

    /*
     * given the input, and having an enhanced grammar, we create the action table,
     * then run the algorithm and transform it into a SyntaxTree
     */
    SyntaxTree run(std::deque<std::string>& input_queue);
};
