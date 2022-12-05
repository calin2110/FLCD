//
// Created by popca on 30/11/2022.
//

#include "../header/Parser.h"


std::unordered_set<LR0Item> Parser::create_closure_LR0(const std::unordered_set<LR0Item>& analysis_items) {
    std::unordered_set<LR0Item> closure{};
    closure.insert(analysis_items.begin(), analysis_items.end());

    bool changed;
    do {
        changed = false;
        std::unordered_set<LR0Item> items_to_add = std::unordered_set<LR0Item>{};
        for (const LR0Item& item: closure) {
            if (!item.rhs.empty() && grammar.nonterminals.find(item.rhs.front()) != grammar.nonterminals.end()) {
                std::list<Production> matching_productions = grammar.productions.find(item.rhs.front())->second;
                for (const Production& prod: matching_productions) {
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

Parser::Parser(const EnhancedCFGGrammar &grammar): grammar(grammar) {}

void Parser::run() {
    auto states = create_col_can_LR0();
//    for (auto state: states) {
//        std::cout << "STATE:\n";
//        for (auto c: state.items) {
//            std::cout << c.start << "->" ;
//            for (auto d: c.lhs) {
//                std::cout << d << " ";
//            }
//            std::cout << ".";
//            for (auto d: c.rhs) {
//                std::cout << d << " ";
//            }
//            std::cout << "\n";
//        }
//        std::cout << "\n";
//    }
}

State Parser::create_goto_LR0(
        const State &state,
        const std::string &element
) {
    std::unordered_set<LR0Item> goto_items{};
    for (const LR0Item& lr0_item: state.items) {
        if (!lr0_item.rhs.empty() && lr0_item.rhs.front() == element) {
            LR0Item shifted_dot = lr0_item.shift_dot_right();
            goto_items.insert(shifted_dot);
        }
    }
    return State(create_closure_LR0(goto_items));
}

std::unordered_set<State> Parser::create_col_can_LR0() {
    std::unordered_set<State> states{};
    const Production& starting_production = grammar.productions.find(grammar.start_symbol)->second.front();
    LR0Item lr0Item = LR0Item(grammar.start_symbol, std::list<std::string>{}, starting_production.rhs);
    states.insert(State(create_closure_LR0(std::unordered_set<LR0Item>{lr0Item})));
    const std::unordered_set<std::string> elements = grammar.get_terminals_and_nonterminals();

    bool changed;
    do {
        changed = false;
        std::unordered_set<State> states_to_add{};

        for (const State& state: states) {
            for (const std::string& element: elements) {
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
