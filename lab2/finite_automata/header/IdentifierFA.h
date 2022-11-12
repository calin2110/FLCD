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
            transitions[state] = std::unordered_map<char, std::list<std::string>>();
        }

        for (char val = 'a'; val <= 'z'; val++) {
            alphabet.insert(val);
            transitions["p"][val] = std::list<std::string>{"q"};
            transitions["q"][val] = std::list<std::string>{"q"};
        }
        for (char val = 'A'; val <= 'Z'; val++) {
            alphabet.insert(val);
            transitions["p"][val] = std::list<std::string>{"q"};
            transitions["q"][val] = std::list<std::string>{"q"};
        }
        alphabet.insert('_');
        transitions["p"]['_'] = std::list<std::string>{"q"};
        transitions["q"]['_'] = std::list<std::string>{"q"};

        for (char val = '0'; val <= '9'; val++) {
            alphabet.insert(val);
            transitions["q"][val] = std::list<std::string>{"q"};
        }

        initial_state = "p";

        final_states.insert("q");
    }

};


