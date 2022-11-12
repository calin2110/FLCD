//
// Created by popca on 11/11/2022.
//

#pragma once


#include <string>
#include <utility>

struct Transition {
    Transition(
            std::string startState,
            std::string endState,
            char value
    ) : start_state(std::move(startState)),
        end_state(std::move(endState)),
        value(value) {

    }

    std::string start_state;
    std::string end_state;
    char value;
};
