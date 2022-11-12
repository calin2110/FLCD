//
// Created by popca on 11/11/2022.
//

#pragma once

class IdentifierFA : public FiniteAutomata {
public:
    IdentifierFA() {
        states.insert("p");
        states.insert("q");

        for (const std::string& state: states) {
            transitions[state] = std::list<Transition>{};
        }

        for (char val = 'a'; val <= 'z'; val++) {
            alphabet.insert(val);
            transitions["p"].emplace_back("p", "q", val);
            transitions["q"].emplace_back("q", "q", val);
        }
        for (char val = 'A'; val <= 'Z'; val++) {
            alphabet.insert(val);
            transitions["p"].emplace_back("p", "q", val);
            transitions["q"].emplace_back("q", "q", val);
        }
        alphabet.insert('_');
        transitions["p"].emplace_back("p", "q", '_');
        transitions["q"].emplace_back("q", "q", '_');

        for (char val = '0'; val <= '9'; val++) {
            alphabet.insert(val);
            transitions["q"].emplace_back("q", "q",val);
        }

        initial_state = "p";

        final_states.insert("q");
    }

};


