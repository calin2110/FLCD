//
// Created by popca on 09/11/2022.
//

#pragma once

class FAFormatException: public std::exception {
private:
    std::string error_message;

public:
    explicit FAFormatException(std::string  error_msg): error_message(std::move(error_msg)) {
    }

    [[nodiscard]] const char* what () const noexcept override {
        return error_message.c_str();
    }
};
