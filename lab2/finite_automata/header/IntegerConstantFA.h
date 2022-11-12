//
// Created by popca on 11/11/2022.
//

#pragma once
#include "FiniteAutomata.h"

class IntegerConstantFA: public FiniteAutomata {
public:
    IntegerConstantFA() {
        states.insert("p");
        states.insert("q");
        states.insert("r");
        states.insert("s");

        for (const std::string& state: states) {
            transitions[state] = std::list<Transition>{};
        }

        for (char value = '1'; value <= '9'; value++) {
            alphabet.insert(value);
            transitions["p"].emplace_back("p", "r", value);
            transitions["q"].emplace_back("q", "r", value);
            transitions["r"].emplace_back("r", "r", value);
        }

        alphabet.insert('0');
        transitions["p"].emplace_back("p", "s", '0');
        transitions["r"].emplace_back("r", "r", '0');

        alphabet.insert('+');
        alphabet.insert('-');
        transitions["p"].emplace_back("p", "q", '+');
        transitions["p"].emplace_back("p", "q", '-');

        initial_state = "p";

        final_states.insert("r");
        final_states.insert("s");
    }

};


