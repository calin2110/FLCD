//
// Created by popca on 09/11/2022.
//

#include "../header/FiniteAutomata.h"
#include "../../exception/NotYetImplementedException.h"
#include "../../exception/FAFormatException.h"

std::istream &operator>>(std::istream &is, FiniteAutomata &object) {
    int number_of_states;
    is >> number_of_states;
    std::unordered_set<std::string> states{};
    for (int _ = 0; _ < number_of_states; _++) {
        std::string state;
        is >> state;
        states.insert(state);
    }

    int alphabet_size;
    is >> alphabet_size;
    std::unordered_set<char> alphabet{};
    for (int _ = 0; _ < alphabet_size; _++) {
        std::string element;
        is >> element;
        if (element.size() != 1) {
            throw FAFormatException(
                    "Element of the alphabet " + element + " must be 1 character long!"
            );
        }
        alphabet.insert(element[0]);
    }

    std::string starting_state;
    is >> starting_state;
    if (states.find(starting_state) == states.end()) {
        throw FAFormatException(
                "Starting state " + starting_state + " is not a state!\n");
    }

    int number_of_transitions;
    is >> number_of_transitions;
    std::unordered_map<std::string, std::unordered_map<char, std::list<std::string>>> transitions{};
    for (const std::string& state: states) {
        transitions[state] = std::unordered_map<char, std::list<std::string>>();
    }

    for (int _ = 0; _ < number_of_transitions; _++) {
        std::string start_transition, end_transition, value_transition;
        is >> start_transition >> value_transition >> end_transition;
        if (value_transition.size() != 1) {
            throw FAFormatException(
                    "The value with which we transition " + value_transition + " must be 1 character long!"
            );
        }

        char value = value_transition[0];
        if (states.find(start_transition) == states.end()) {
            throw FAFormatException(
            "The starting state of a transition " + start_transition + " must be a state!"
            );
        }

        if (states.find(end_transition) == states.end()) {
            throw FAFormatException(
                    "The ending state of a transition " + end_transition + " must be a state!"
            );
        }

        if (alphabet.find(value) == alphabet.end()) {
            std::string error_message =  "The value with which we transition ";
            error_message.push_back(value);
            error_message += " is not in the alphabet!";
            throw FAFormatException(
                error_message
            );
        }

        if (transitions[start_transition].find(value) ==
                transitions[start_transition].end()) {
            transitions[start_transition][value] = std::list<std::string>();
        }

        transitions[start_transition][value].push_back(end_transition);
    }

    int number_of_final_states;
    is >> number_of_final_states;
    std::unordered_set<std::string> final_states{};
    for (int _ = 0; _ < number_of_final_states; _++) {
        std::string final_state;
        is >> final_state;
        if (states.find(final_state) == states.end()) {
            throw FAFormatException(
                    "Final state " + final_state + " must be a state!"
            );
        }
        final_states.insert(final_state);
    }

    object.states = states;
    object.transitions = transitions;
    object.initial_state = starting_state;
    object.alphabet = alphabet;
    object.final_states = final_states;
    return is;
}

void FiniteAutomata::print_states(std::ostream &os) {
    os << "STATES:\n";
    for (const std::string& state: states) {
        os << state << " ";
    }
    os << "\n\n";
}

void FiniteAutomata::print_transitions(std::ostream &os) {
    os << "TRANSITIONS:\n";
    for (const auto& key_to_transitions: transitions) {
        for (const auto& transition:
                key_to_transitions.second) {
            for (const std::string& value: transition.second) {
                os << "d(" << key_to_transitions.first << ", ";
                os << transition.first << ")= ";
                os << value << "\n";
            }
        }
    }
    os << "\n\n";
}

void FiniteAutomata::print_alphabet(std::ostream &os) {
    os << "ALPHABET:\n";
    for (const char& element: alphabet) {
        os << element << " ";
    }
    os << "\n\n";
}

void FiniteAutomata::print_initial_state(std::ostream &os) {
    os << "INITIAL STATE: " << initial_state << "\n\n";
}

void FiniteAutomata::print_final_states(std::ostream &os) {
    os << "FINAL STATES:\n";
    for (const std::string& final_state: final_states) {
        os << final_state << " ";
    }
    os << "\n\n";
}

bool FiniteAutomata::is_deterministic() {
    for (const auto& something: transitions) {
        for (const auto& transition: something.second) {
            if (transition.second.size() != 1) {
                return false;
            }
        }
    }
    return true;
}

bool FiniteAutomata::is_sequence_accepted(const std::string &sequence) {
    if (!is_deterministic()) {
        throw NotYetImplementedException(
                "Checking whether sequences are accepted have not yet been implemented"
                " for non-deterministic FAs!"
        );
    }
    if (final_states.find(initial_state) != final_states.end() && sequence.empty()) {
        return true;
    }
    for (const char& elem: sequence) {
        if (alphabet.find(elem) == alphabet.end()) {
            return false;
        }
    }
    std::string current_state = initial_state;
    int current_index = 0;
    while (current_index < sequence.length()) {
        char current_character = sequence[current_index];
        std::unordered_map<char, std::list<std::string>> current_transitions = transitions[current_state];
        if (current_transitions.find(current_character) == current_transitions.end()) {
            return false;
        }
        current_state = current_transitions[current_character].front();
        current_index++;
    }
    return final_states.find(current_state) != final_states.end();
}

