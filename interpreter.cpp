#include "commands.h"
#include "interpreter.h"
#include <iostream>


Interpreter &Interpreter::getInstance() {
    static Interpreter i;
    return i;
}

bool Interpreter::registerCreator(const creator_t &creator, const std::string &c) {
    creators_[c] = creator;
    return true;
}

std::vector<std::unique_ptr<Command>>
Interpreter::getCommands(std::string::const_iterator &it, const std::string::const_iterator &end, std::function<bool(const std::string &)> stopCondition) {
    std::vector<std::unique_ptr<Command>> cmds;
    do {
        it = skipSpaces(it, end);
        if (it == end)
            return cmds;

//        if (stopCondition(it, end)) {
//            return cmds;
//        }

        auto word_end = std::find_if(it, end, [](char c) { return std::isspace(c); });
        std::string word = std::string(it, word_end);

        if (stopCondition(word)) {
            return cmds;
        }

        if (isStringStart(word)) {
            // CR: ."
            it = ++word_end;
            std::string content = getStringContent(it, end);
            cmds.push_back(std::make_unique<ParseString>(ParseString(content)));
            continue;
        }

        if (isDigit(word)) {
            cmds.push_back(std::make_unique<PushDigit>(PushDigit(std::stoi(word))));
            it = word_end;
            continue;
        }

        auto creator_it = creators_.find(word);
        if (creator_it == creators_.end() && !isKeyWord(word)) {
            std::stringstream strError;
            strError << "no such command : '" << word << "'";
            throw interpreter_error(strError.str());
        }

        it = word_end;

        if (!isKeyWord(word)) {
            creator_t creator = (*creator_it).second;
            cmds.push_back(creator(it, end));
        }

    } while (it != end);

    return cmds;
}

std::expected<std::string, std::string>
Interpreter::interpret(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    std::stringstream out;
    context cntx = {stack_, std::move(out)};

    try {
        auto it = begin;

        const std::vector<std::unique_ptr<Command>> cmds = getCommands(it, end);
        for (auto &cmd: cmds) {
            cmd->apply(cntx);
        }

    } catch (interpreter_error &e) {
        return std::unexpected<std::string>(e.what());
    }

    return cntx.out.str();
}

std::string::const_iterator
Interpreter::skipSpaces(std::string::const_iterator &it, const std::string::const_iterator &end) {
    return std::find_if(it, end, [](char c) { return !std::isspace(c); });
}

std::string Interpreter::getStringContent(std::string::const_iterator &it, const std::string::const_iterator &end) {
    auto quotePos = find_if(it, end, [](char c) { return c == '\"'; });
    if (quotePos == end) {
        throw interpreter_error("no closing quotation mark for printing string");
    }

    std::string content = std::string(it, quotePos);
    it = ++quotePos;
    return content;
}

bool Interpreter::stopCondition(std::string::const_iterator &it, const std::string::const_iterator &end) {
    auto word_end = std::find_if(it, end, [](char c) { return std::isspace(c); });
    std::string word = std::string(it, word_end);

    if (word == "else") {
        it = ++word_end;
        return true;
    }

    if (word == "then") {
        if (*(++word_end) == ';') {
            it = word_end;
        } else {
            throw interpreter_error("no ';' for 'if'");
        }
        return true;
    }

    return false;
}

bool Interpreter::isKeyWord(std::string &str) {
    return str == "i";
}

bool Interpreter::isStringStart(const std::string &str) {
    // CR: f."
    return str.find(".\"") != std::string::npos;
}

bool Interpreter::isDigit(const std::string &str) {
    // CR: -22
    return str.find_first_not_of("0123456789") == std::string::npos;
}

void Interpreter::clearStack() {
    while (stack_.size() != 0) {
        stack_.pop();
    }
}