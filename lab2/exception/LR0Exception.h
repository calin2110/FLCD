//
// Created by popca on 14/12/2022.
//

#pragma once
#include <string>
#include <deque>
#include <list>

class LR0Exception: public std::exception {
private:
    std::string error_message;

public:
    explicit LR0Exception(const std::string& error_msg, const std::deque<std::string>& input) {
        error_message = error_msg + ": ";
        for (const std::string& input_item: input) {
            error_message += input_item + " ";
        }
    }

    [[nodiscard]] const char* what () const noexcept override {
        return error_message.c_str();
    }
};
