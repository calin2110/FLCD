//
// Created by popca on 09/11/2022.
//

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <list>
#include <fstream>


class FiniteAutomata {
protected:
    std::unordered_set<std::string> states;
    std::unordered_set<char> alphabet;
    std::unordered_map<std::string, std::unordered_map<char, std::list<std::string>>> transitions;
    std::string initial_state;
    std::unordered_set<std::string> final_states;

public:

    friend std::istream &operator>>(std::istream &is, FiniteAutomata &object);

    void print_transitions(std::ostream &os);

    void print_alphabet(std::ostream &os);

    void print_initial_state(std::ostream &os);

    void print_final_states(std::ostream &os);

    void print_states(std::ostream &os);

    bool is_deterministic();

    bool is_sequence_accepted(const std::string &sequence);
};


