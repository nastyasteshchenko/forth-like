#include "interpreter.h"
#include "interpreter_error.h"

Interpreter &Interpreter::getInstance() {
    static Interpreter i;
    return i;
}

bool Interpreter::registerCreator(const creator_t &creator, const std::string &c) {
    creators_[c] = creator;
    return true;
}

void
Interpreter::getAndApplyCommands(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    for (auto it = begin; it < end; it++) {
        std::stringstream ss;
        for (; *it != ' ' && *it != '\0'; it++) {
            if (*it == '\"') break;
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
        creator_t creator = (*creator_it).second;
        Command *cmd = creator(it, end);
        cmd->apply(it_, buf_);
        delete cmd;
    }
}

void Interpreter::interpret(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    try {
        buf_.clear();
        getAndApplyCommands(begin, end);
        if (!buf_.str().empty()) {
            std::cout <<"< "<< buf_.str() << std::endl;
        } else {
            std::cout << "< ok" << std::endl;
        }
    } catch (interpreter_error &e) {
        std::cerr << e.what() << std::endl;
    }
}

std::stack<int> Interpreter::operator*() {
    return *it_;
}

