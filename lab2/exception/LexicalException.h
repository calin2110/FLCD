#include <utility>

//
// Created by popca on 31/10/2022.
//

#pragma once


class LexicalException: public std::exception {
private:
    std::string error_message;

public:
    explicit LexicalException(std::string  error_msg): error_message(std::move(error_msg)) {
    }

    [[nodiscard]] const char* what () const noexcept override {
        return error_message.c_str();
    }
};


