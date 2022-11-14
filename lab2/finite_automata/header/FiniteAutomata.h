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
    // a state is a std::string, as states are unique we may use
    // an std::unordered_set to keep them in memory so searching for a state is theta(1) amortized
    std::unordered_set<std::string> states;
    // an element of the alphabet is a char, as elements are unique we may use
    // an std::unordered_set to keep them in memory so searching for a char is theta(1) amortized
    std::unordered_set<char> alphabet;
    // as transitions have a starting state which is a std::string and a value with which we transition to,
    // we may use an std::unordered_map mapping from each state (std::string) to
    // an std::unordered_map mapping from each alphabet element (char) to a std::list of std::string representing
    // the states to which we can transition with the given char
    // we do not care enough to use an std::unordered_set instead of a std::list because iterating is theta(n) for each
    std::unordered_map<std::string, std::unordered_map<char, std::list<std::string>>> transitions;
    // a std::string representing the initial_state of the FA
    std::string initial_state;
    // as states are std::string and unique we may use
    // an std::unordered_set<std::string> for the final states, so searching for a final state is theta(1) amortized
    std::unordered_set<std::string> final_states;

public:

    friend std::istream &operator>>(std::istream &is, FiniteAutomata &object);

    void print_transitions(std::ostream &os);

    void print_alphabet(std::ostream &os);

    void print_initial_state(std::ostream &os);

    void print_final_states(std::ostream &os);

    void print_states(std::ostream &os);

    /**
     * Given a FA, we check whether it is deterministic or not by checking whether all std::list<std::string> in the transitions
     * have the length exactly 1
     *
     * @return: true if the FA is deterministic, false otherwise
     */
    bool is_deterministic();

    /**
     * Given a FA, we check whether it accepts a given sequence which is a std::string
     * by trying to get from the initial_state to the final_state using characters of the string
     * and transitions
     *
     * @param sequence: std::string representing the sequence to be checked whether is accepted by the FA or not
     * @return: true if the FA accepts our sequence, false otherwise
     * @throws: NotYetImplementedException if the FA is not deterministic
     */
    bool is_sequence_accepted(const std::string &sequence);
};


