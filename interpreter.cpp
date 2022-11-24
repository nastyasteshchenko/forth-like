#pragma once

#include <sstream>
#include <iostream>
#include "interpreter_error.h"
#include <string>
#include "interpreter.h"

Interpreter &Interpreter::getInstance() {
    static Interpreter i;
    return i;
}

bool Interpreter::registerCreator(const creator_t &creator, const std::string &c) {
    creators_[c] = creator;
    return true;
}

void Interpreter::getAndApplyCommands(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    int countPrintCmds = 0;
    for (auto it = begin; it < end; it++) {
        std::stringstream ss;
        for (; *it != ' ' && *it != '\0'; it++) {
            if (*it == '\"') {
                break;
            }
            ss << *it;
        }
        char *e;
        int val = std::strtol(ss.str().data(), &e, 10);
        if (val != 0 || ss.str() == "0") {
            it_.push(val);
            continue;
        }
        auto creator_it = creators_.find(ss.str());
        if (creator_it == creators_.end()) {
            std::stringstream strError;
            strError << "no such command : '" << ss.str() << "'";
            throw interpreter_error(strError.str());
        }
        if (ss.str() == "." || ss.str() == "cr" || ss.str() == "emit" || ss.str() == "if") {
            countPrintCmds++;
        }
        creator_t creator = (*creator_it).second;
        Command *cmd = creator(it, end);
        cmd->apply(it_);
        delete cmd;
    }
    if (countPrintCmds == 0) {
        std::cout << "< ";
        std::cout << "ok" << std::endl;
    }
}

void Interpreter::interpret(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    try {
        getAndApplyCommands(begin, end);
    } catch (interpreter_error &e) {
        std::cerr << e.what() << std::endl;
    }
}

std::stack<int> Interpreter::operator*() {
    return *it_;
}

