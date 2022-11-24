#pragma once

#include "commands.h"
#include <iostream>
#include <functional>
#include <stack>
#include "data.h"
#include <unordered_map>
#include <sstream>
#include "smart_pointer.h"

class Interpreter {
public:

    typedef std::function<SmartPointer<Command>(std::string::const_iterator &,
                                                const std::string::const_iterator &)> creator_t;

    static Interpreter &getInstance();

    bool registerCreator(const creator_t &creator, const std::string &c);

    void getAndApplyCommands(const std::string::const_iterator &begin, const std::string::const_iterator &end);

    void interpret(const std::string::const_iterator &begin, const std::string::const_iterator &end);

    std::stack<int> operator*();

private:

    Interpreter() = default;

    Interpreter(Interpreter &other) = delete;

    Interpreter &operator=(const Interpreter &other) = delete;

    std::unordered_map<std::string, creator_t> creators_;

    data it_;

    std::stringstream buf_;
};
