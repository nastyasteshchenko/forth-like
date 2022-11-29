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

//std::vector<Command *> Interpreter::getCommands(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
//    std::vector<Command *> cmds;
//    for () {
//        if (is_digit()) {
//            int n = parse_digit();
//            cmds.push_back(Push(n));
//            continue;
//        }
//
//        auto creator_it = creators_.find(ss.str());
//        if (creator_it == creators_.end()) {
//            std::stringstream strError;
//            strError << "no such command : '" << ss.str() << "'";
//            throw interpreter_error(strError.str());
//        }
//        creator_t creator = (*creator_it).second;
//        cmds.push_back(creator(it, end));
//    }
//}

void
Interpreter::getAndApplyCommands(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    for (auto it = begin; it < end; it++) {
        // ."
        if (is_string_start()) {
            // std::find_if(.", end(), "\"");
            std::string str = parse_string();
            std::cout << str << std::endl;
            continue;
        }
        // 1, 2, ... (https://en.cppreference.com/w/cpp/string/byte/isdigit)
        if (is_digit()) {
            int n = parse_digit();
            it_.push(n);
            continue;
        }


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
        SmartPointer<Command> cmd = creator(it, end);
        (*cmd).apply(it_, buf_);
    }
}

// https://en.cppreference.com/w/cpp/utility/expected
void Interpreter::interpret(const std::string::const_iterator &begin, const std::string::const_iterator &end) {
    try {
        buf_.str("");
        getAndApplyCommands(begin, end);
        if (!buf_.str().empty()) {
            std::cout << "< " << buf_.str() << std::endl;
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

