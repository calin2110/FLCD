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
            transitions[state] = std::unordered_map<char, std::list<std::string>>();
        }

        for (char value = '1'; value <= '9'; value++) {
            alphabet.insert(value);
            transitions["p"][value] = std::list<std::string>{"r"};
            transitions["q"][value] = std::list<std::string>{"r"};
            transitions["r"][value] = std::list<std::string>{"r"};
        }

        alphabet.insert('0');
        transitions["p"]['0'] = std::list<std::string>{"s"};
        transitions["r"]['0'] = std::list<std::string>{"r"};

        alphabet.insert('+');
        alphabet.insert('-');
        transitions["p"]['+'] = std::list<std::string>{"q"};
        transitions["p"]['-'] = std::list<std::string>{"q"};

        initial_state = "p";

        final_states.insert("r");
        final_states.insert("s");
    }

};


