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
    bool registerCreator(const creator_t &, const std::string &);

    //finds commands and digits in a user-supplied string
    //returns vector of commands
    std::vector<std::unique_ptr<Command>>
    getCommands(std::string::const_iterator &, const std::string::const_iterator &);

    //applies commands and catches exceptions
    //returns the string containing the exception if catches an error
    //returns the string containing result of applying commands otherwise
    std::expected<std::string, std::string>
    interpret(const std::string::const_iterator &, const std::string::const_iterator &);

    //clears stack of digits
    void clearStack();

private:

    friend Command;

    Interpreter() = default;

    Interpreter(Interpreter &) = delete;

    Interpreter &operator=(const Interpreter &) = delete;

    std::unordered_map<std::string, creator_t> creators_;

    data stack_;

    std::string::const_iterator skipSpaces(std::string::const_iterator &, const std::string::const_iterator &);

    std::string getStringContent(std::string::const_iterator &, const std::string::const_iterator &);

    bool isKeyWord(std::string &);

    bool stopCondition(std::string::const_iterator &, const std::string::const_iterator &);

    bool isSrtingStart(const std::string &);

    bool isDigit(const std::string &);
};
