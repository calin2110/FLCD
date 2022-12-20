//
// Created by popca on 14/12/2022.
//

#pragma once

class ConflictException: public std::exception {
private:
    std::string error_message;

public:
    explicit ConflictException(const std::string& conflict_type) {
        error_message = conflict_type + " found in the action table!";
    }

    [[nodiscard]] const char* what () const noexcept override {
        return error_message.c_str();
    }
};
