#pragma once

#include "commands.h"
#include "data_stack.h"
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
    static Interpreter &getInstance();

    //registers commands
    //returns true
    bool registerCreator(const creator_t &, const std::string &);

    //delete command creator
    //returns true
    bool deRegisterCreator(const std::string &);

    //finds commands and digits in a user-supplied string
    //returns vector of commands
    std::vector<std::unique_ptr<Command>>
    getCommands(std::string::const_iterator &, const std::string::const_iterator &, std::function<bool(const std::string &)>);

    //applies commands and catches exceptions
    //returns the string containing the exception if an error was catches
    //returns the string containing result of applying commands otherwise
    std::expected<std::string, std::string>
    interpret(const std::string::const_iterator &, const std::string::const_iterator &);

private:

    friend Command;

    Interpreter() = default;

    Interpreter(Interpreter &) = delete;

    Interpreter &operator=(const Interpreter &) = delete;

    std::unordered_map<std::string, creator_t> creators_;

    dataStack stack_;

    std::string::const_iterator skipSpaces(std::string::const_iterator &, const std::string::const_iterator &);

    std::string getStringContent(std::string::const_iterator &, const std::string::const_iterator &);

    bool isStringStart(const std::string &);

    bool isDigit( std::string);
};
