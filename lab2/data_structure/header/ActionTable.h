//
// Created by popca on 12/12/2022.
//

#pragma once
#include <unordered_map>
#include "../../model/header/State.h"
#include "../../model/header/Actions.h"

class ActionTable {
private:
    std::unordered_map<State, std::unordered_map<std::string, State>> go_to_table;
    std::unordered_map<State, Action*> action_table;
    void add_state(const State& state);

public:
    ActionTable();
    void add_go_to(const State& state, const std::string& element, const State& go_to_state);
    void compute_actions(const Production& start_production);
    friend std::ostream &operator<<(std::ostream &os, ActionTable& object);
    static std::ostream& print_action(std::ostream& os, Action* action);
    void print_conflicts();
    Action* find_action_for_state(const State& state);
    bool is_goto_for_state(const State& state, const std::string& element);
    State find_goto_for_state(const State& state, const std::string& element);

    ~ActionTable();
};