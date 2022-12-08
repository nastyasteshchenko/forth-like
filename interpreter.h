#pragma once

#include "commands.h"
#include "data.h"
#include <expected>
#include <functional>
#include <vector>
#include <memory>
#include <stack>
#include <unordered_map>

class Interpreter {
public:

    typedef std::function<std::unique_ptr<Command>(std::string::const_iterator &,
                                                   const std::string::const_iterator &)> creator_t;

    //creates a single instance of the class
    //returns a single instance of the class
    static Interpreter &getInstance();

    //registers commands
    //returns true
    bool registerCreator(const creator_t &creator, const std::string &c);

    //finds commands and digits in a user-supplied string
    //returns vector of commands
    std::vector<std::unique_ptr<Command>>
    getCommands(const std::string::const_iterator &begin, const std::string::const_iterator &end);

    //applies commands and catches exceptions
    //returns the string containing the exception if catches an error
    //returns the string containing result of applying commands otherwise
    std::expected<std::string, std::string>
    interpret(const std::string::const_iterator &begin, const std::string::const_iterator &end);

    //clears stack of digits
    void clearStack();

private:

    Interpreter() = default;

    Interpreter(Interpreter &other) = delete;

    Interpreter &operator=(const Interpreter &other) = delete;

    std::unordered_map<std::string, creator_t> creators_;

    context cntx_;

    bool isStringStart(const std::string &str);

    bool isDigit(const std::string &str);
};
