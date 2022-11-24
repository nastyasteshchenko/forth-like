#pragma once

#include <stdexcept>

class interpreter_error: public std::runtime_error {
public:

    explicit interpreter_error(const std::string & msg): std::runtime_error(msg) {}

};