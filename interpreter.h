#pragma once

#include "commands.h"
#include <functional>
#include <unordered_map>

class Interpreter {
public:

    typedef std::function<Command *(std::string::const_iterator &, const std::string::const_iterator &)> creator_t;

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
};
