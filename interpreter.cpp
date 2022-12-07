#include "commands.h"
#include "interpreter.h"

Interpreter &Interpreter::getInstance() {
    static Interpreter i;
    return i;
}

bool Interpreter::registerCreator(const creator_t &creator, const std::string &c) {
    creators_[c] = creator;
    return true;
}

std::vector<std::unique_ptr<Command>>
Interpreter::getCommands(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    std::vector<std::unique_ptr<Command>> cmds;
    for (auto it = begin; it < end; it++) {
        std::stringstream ss;
        for (; *it != ' ' && *it != '\0'; it++) {
            ss << *it;
        }
        if (!ss.str().empty()) {
            if (isSrtingStart(ss.str())) {
                    it++;
                    for (; *it != ' ' && *it != '\0'; it++) {
                        ss << *it;
                }
                cmds.push_back(std::unique_ptr<Command>(new ParseString(ss.str())));
                continue;
            }
            if (isDigit(ss.str())) {
                char *e;
                cmds.push_back(std::unique_ptr<Command>(new ParseDigit(std::strtol(ss.str().data(), &e, 10))));
                continue;
            }
            auto creator_it = creators_.find(ss.str());
            if (creator_it == creators_.end()) {
                std::stringstream strError;
                strError << "no such command : '" << ss.str() << "'";
                throw interpreter_error(strError.str());
            }
            creator_t creator = (*creator_it).second;
            cmds.push_back(creator(it, end));
        }
    }
    return cmds;
}

std::expected<std::string, std::string>
Interpreter::interpret(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    try {
        cntx_.out.str("");
        const std::vector<std::unique_ptr<Command>> cmds = getCommands(begin, end);
        for (auto &cmd: cmds) {
            cmd->apply(cntx_);
        }
    } catch (interpreter_error &e) {
        return std::unexpected<std::string>(e.what());
    }
    return cntx_.out.str().data();
}

bool Interpreter::isSrtingStart(const std::string &str) {
    return str.find(".\"") != std::string::npos;
}

bool Interpreter::isDigit(const std::string &str) {
    return str.find_first_not_of("0123456789") == std::string::npos;
}

void Interpreter::clearStack() {
    while (cntx_.stack.size() != 0) {
        cntx_.stack.pop();
    }
}