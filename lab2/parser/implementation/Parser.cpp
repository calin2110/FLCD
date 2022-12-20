//
// Created by popca on 30/11/2022.
//

#include "../header/Parser.h"
#include "../../data_structure/header/ActionTable.h"
#include "../../exception/LR0Exception.h"
#include "../../exception/ConflictException.h"

#include <utility>
#include <stack>

std::unordered_set<LR0Item> Parser::create_closure_LR0(const std::unordered_set<LR0Item> &analysis_items) {
    std::unordered_set<LR0Item> closure{};
    closure.insert(analysis_items.begin(), analysis_items.end());

    bool changed;
    do {
        changed = false;
        std::unordered_set<LR0Item> items_to_add = std::unordered_set<LR0Item>{};
        for (const LR0Item &item: closure) {
            if (!item.rhs.empty() && grammar.nonterminals.find(item.rhs.front()) != grammar.nonterminals.end()) {
                std::list<Production> matching_productions = grammar.productions[item.rhs.front()];
                for (const Production &prod: matching_productions) {
                    LR0Item lrItm = LR0Item(item.rhs.front(), std::list<std::string>{}, prod.rhs);
                    if (closure.find(lrItm) == closure.end()) {
                        changed = true;
                        items_to_add.insert(lrItm);
                    }
                }
            }
        }
        closure.insert(items_to_add.begin(), items_to_add.end());
    } while (changed);

    closure.insert(analysis_items.begin(), analysis_items.end());
    return closure;
}

Parser::Parser(EnhancedCFGGrammar grammar) : grammar(std::move(grammar)) {}

SyntaxTree Parser::run(std::deque<std::string> &input_queue) {
    std::unordered_set<State> states = create_col_can_LR0();
    ActionTable action_table = create_action_table(states);
    std::list<Production> output_band = run_algorithm(input_queue, action_table);

    std::string start_point = grammar.productions[grammar.start_symbol].front().rhs.front();
    SyntaxTree parsingTree{start_point, grammar.nonterminals};
    for (const Production &prod: output_band) {
        parsingTree.parse_production(prod);
    }

    return parsingTree;
}

State Parser::create_goto_LR0(
        const State &state,
        const std::string &element
) {
    std::unordered_set<LR0Item> goto_items{};
    for (const LR0Item &lr0_item: state.items) {
        if (!lr0_item.rhs.empty() && lr0_item.rhs.front() == element) {
            LR0Item shifted_dot = lr0_item.shift_dot_right();
            goto_items.insert(shifted_dot);
        }
    }
    return State(create_closure_LR0(goto_items));
}

std::unordered_set<State> Parser::create_col_can_LR0() {
    std::unordered_set<State> states{};
    const Production &starting_production = grammar.productions[grammar.start_symbol].front();
    LR0Item lr0Item = LR0Item(grammar.start_symbol, std::list<std::string>{}, starting_production.rhs);
    states.insert(State(create_closure_LR0(std::unordered_set<LR0Item>{lr0Item})));
    const std::unordered_set<std::string> elements = grammar.get_terminals_and_nonterminals();

    bool changed;
    do {
        changed = false;
        std::unordered_set<State> states_to_add{};

        for (const State &state: states) {
            for (const std::string &element: elements) {
                State current_go_to = create_goto_LR0(state, element);
                if (!current_go_to.empty() && states.find(current_go_to) == states.end()) {
                    states_to_add.insert(current_go_to);
                    changed = true;
                }
            }
        }
        states.insert(states_to_add.begin(), states_to_add.end());
    } while (changed);

    return states;
}

ActionTable Parser::create_action_table(const std::unordered_set<State> &states) {
    ActionTable table = ActionTable(states);
    std::unordered_set<std::string> alphabet = grammar.get_terminals_and_nonterminals();
    for (const State &state: states) {
        for (const std::string &element: alphabet) {
            State go_to_state = create_goto_LR0(state, element);
            if (!go_to_state.empty()) {
                table.add_go_to(state, element, go_to_state);
            }
        }
    }
    table.compute_actions(grammar.productions[grammar.start_symbol].front());
    return table;
}

std::list<Production> Parser::run_algorithm(std::deque<std::string> &input_deque, ActionTable &action_table) {
    std::stack<std::string> working_string_stack = std::stack<std::string>{};
    std::stack<State> working_state_stack = std::stack<State>{};
    std::list<Production> output_band{};

    const Production &starting_production = grammar.productions[grammar.start_symbol].front();
    LR0Item lr0Item = LR0Item(grammar.start_symbol, std::list<std::string>{}, starting_production.rhs);
    working_state_stack.push(State(create_closure_LR0(std::unordered_set<LR0Item>{lr0Item})));
    bool done = false;

    std::string first;
    State new_state;

    Production production = Production(std::list<std::string>{}, std::list<std::string>{});

    while (!done) {
        if (working_state_stack.empty()) {
            throw LR0Exception("Working state stack is empty", input_deque);
        }
        Action *action = action_table.find_action_for_state(working_state_stack.top());
        switch (action->type()) {
            case ActionType::SHIFT:
                if (input_deque.empty()) {
                    throw LR0Exception("There is no input left", input_deque);
                }
                first = input_deque.front();
                input_deque.pop_front();
                if (!action_table.is_goto_for_state(working_state_stack.top(), first)) {
                    throw LR0Exception("We cannot go from current state to where we would need to", input_deque);
                }
                new_state = action_table.find_goto_for_state(working_state_stack.top(), first);
                working_string_stack.push(first);
                working_state_stack.push(new_state);
                break;
            case ActionType::REDUCE:
                production = dynamic_cast<ReduceAction *>(action)->production;
                for (auto iterator = production.rhs.rbegin(); iterator != production.rhs.rend(); iterator++) {
                    if (working_state_stack.empty() || working_string_stack.empty()) {
                        throw LR0Exception("Either working stacks is empty", input_deque);
                    }
                    if (working_string_stack.top() != *iterator) {
                        throw LR0Exception("Strings must match the ones in the production", input_deque);
                    }
                    working_string_stack.pop();
                    working_state_stack.pop();
                }
                input_deque.emplace_front(production.lhs.front());
                output_band.push_front(production);
                break;
            case ActionType::ERROR:
                throw LR0Exception("Error state found", input_deque);
            case ActionType::ACCEPT:
                done = true;
                break;
            case ActionType::SHIFT_REDUCE_CONFLICT:
                throw ConflictException("Shift Reduce");
            case ActionType::REDUCE_REDUCE_CONFLICT:
                throw ConflictException("Reduce Reduce");
        }
    }
    return output_band;
}