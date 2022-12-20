//
// Created by popca on 12/12/2022.
//

#include "../header/ActionTable.h"

#include <utility>
#include <algorithm>

ActionTable::ActionTable(const std::unordered_set<State> &states) {
    go_to_table = std::unordered_map<State, std::unordered_map<std::string, State>>{};
    action_table = std::unordered_map<State, Action *>{};
    for (const State &state: states) {
        go_to_table[state] = std::unordered_map<std::string, State>{};
        action_table[state] = nullptr;
    }
}

void ActionTable::add_go_to(const State &state, const std::string &element, const State &go_to_state) {
    go_to_table[state][element] = go_to_state;
}

void ActionTable::compute_actions(const Production &start_production) {
    for (const auto &pair: action_table) {
        const State state = pair.first;
        const std::unordered_set<LR0Item> items = state.items;

        // shift: all items are of type [ A -> a.b], where b is not empty
        bool is_shift =
                std::all_of(items.begin(), items.end(), [](const LR0Item &lr0Item) {
                    return !lr0Item.rhs.empty();
                });
        if (is_shift) {
            action_table[state] = new ShiftAction();
            continue;
        }

        // accept: the item [S' -> S.] is contained
        LR0Item acceptItem = LR0Item(start_production.lhs.front(), start_production.rhs, std::list<std::string>{});
        if (items.find(acceptItem) != items.end()) {
            action_table[state] = new AcceptAction();
            continue;
        }

        // reduce: it has only one item and it is [A -> b.]
        bool is_reduce = items.size() == 1 &&
                         std::all_of(items.begin(), items.end(), [](const LR0Item &lr0Item) {
                             return lr0Item.rhs.empty();
                         });
        if (is_reduce) {
            LR0Item item = *items.begin();
            std::list<std::string> rhs = std::list<std::string>{};
            rhs.insert(rhs.end(), item.lhs.begin(), item.lhs.end());
            action_table[state] = new ReduceAction(Production(
                    std::list<std::string>{item.start},
                    rhs
            ));
            continue;
        }

        // error: has no gotos but is not reduce or accept
        if (go_to_table[state].empty()) {
            action_table[state] = new ErrorAction();
            continue;
        }

        auto reduce_iterator = std::find_if(items.begin(), items.end(), [](const LR0Item &lr0Item) {
            return lr0Item.rhs.empty();
        });

        auto shift_iterator = std::find_if(items.begin(), items.end(), [](const LR0Item &lr0Item) {
            return !lr0Item.rhs.empty();
        });

        if (reduce_iterator != items.end()) {
            // shift reduce conflict: there is a [A -> a.b] item with b non empty
            // and a [A -> c.] item
            if (shift_iterator != items.end()) {
                action_table[state] = new ShiftReduceConflict(*shift_iterator, *reduce_iterator);
                continue;
            }

            LR0Item first_reduce_item = *reduce_iterator;
            std::advance(reduce_iterator, 1);
            auto second_reduce_iterator = std::find_if(reduce_iterator, items.end(), [](const LR0Item &lr0Item) {
                return lr0Item.rhs.empty();
            });

            // reduce reduce conflict: there are two items of the type [A -> b.]
            // with different productions
            if (second_reduce_iterator != items.end()) {
                action_table[state] = new ReduceReduceConflict(first_reduce_item, *second_reduce_iterator);
                continue;
            }
        }

        // clearly something went really wrong
        throw std::invalid_argument("Something went really wrong when assigning states!");
    }
}

ActionTable::~ActionTable() {
    for (const auto& pair: action_table) {
        switch (pair.second->type()) {
            case ActionType::SHIFT:
                delete dynamic_cast<ShiftAction*>(pair.second);
                break;
            case ActionType::REDUCE:
                delete dynamic_cast<ReduceAction*>(pair.second);
                break;
            case ActionType::ERROR:
                delete dynamic_cast<ErrorAction*>(pair.second);
                break;
            case ActionType::ACCEPT:
                delete dynamic_cast<AcceptAction*>(pair.second);
                break;
            case ActionType::SHIFT_REDUCE_CONFLICT:
                delete dynamic_cast<ShiftReduceConflict*>(pair.second);
                break;
            case ActionType::REDUCE_REDUCE_CONFLICT:
                delete dynamic_cast<ReduceReduceConflict*>(pair.second);
                break;
        }
        action_table[pair.first] = nullptr;
    }
}

std::ostream &operator<<(std::ostream &os, ActionTable &object) {
    for (const auto& pair: object.action_table) {
        State state = pair.first;
        os << state;
        ActionTable::print_action(std::cout, pair.second);
        for (const auto& go_to_pair: object.go_to_table[state]) {
            os << go_to_pair.first << ":\n" << go_to_pair.second << "\n";
        }
        os << "\n\n";
    }
    return os;
}

std::ostream& ActionTable::print_action(std::ostream &os, Action* action) {
    switch (action->type()) {

        case ActionType::SHIFT:
            os << *dynamic_cast<ShiftAction*>(action) << "\n";
            return os;
        case ActionType::REDUCE:
            os << *dynamic_cast<ReduceAction*>(action) << "\n";
            return os;
        case ActionType::ERROR:
            os << *dynamic_cast<ErrorAction*>(action) << "\n";
            return os;
        case ActionType::ACCEPT:
            os << *dynamic_cast<AcceptAction*>(action) << "\n";
            return os;
        case ActionType::SHIFT_REDUCE_CONFLICT:
            os << *dynamic_cast<ShiftReduceConflict*>(action) << "\n";
            return os;
        case ActionType::REDUCE_REDUCE_CONFLICT:
            os << *dynamic_cast<ReduceReduceConflict*>(action) << "\n";
            return os;
    }
    return os;
}

void ActionTable::print_conflicts() {
    for (const auto& x: action_table) {
        if (x.second->type() == ActionType::SHIFT_REDUCE_CONFLICT) {
            std::cout << *(ShiftReduceConflict*)x.second << "\n";
        }
        if (x.second->type() == ActionType::REDUCE_REDUCE_CONFLICT) {
            std::cout << *(ReduceReduceConflict*)x.second << "\n";
        }
    }
}

Action *ActionTable::find_action_for_state(const State &state) {
    return action_table[state];
}

bool ActionTable::is_goto_for_state(const State &state, const std::string &element) {
    return go_to_table[state].find(element) != go_to_table[state].end();
}

State ActionTable::find_goto_for_state(const State &state, const std::string &element) {
    return go_to_table[state][element];
}
