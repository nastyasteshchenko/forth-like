#include "commands.h"
#include "interpreter.h"
#include "interpreter_error.h"

namespace {

    std::unique_ptr<Command> addCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Plus>();
    }

    bool addOp = Interpreter::getInstance().registerCreator(addCreator, "+");

    std::unique_ptr<Command> subCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Minus>();
    }

    bool subOp = Interpreter::getInstance().registerCreator(subCreator, "-");

    std::unique_ptr<Command> mulCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Mul>();
    }

    bool mulOp = Interpreter::getInstance().registerCreator(mulCreator, "*");

    std::unique_ptr<Command> devCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Div>();
    }

    bool devOp = Interpreter::getInstance().registerCreator(devCreator, "/");

    std::unique_ptr<Command> modCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Mod>();
    }

    bool modOp = Interpreter::getInstance().registerCreator(modCreator, "mod");

    std::unique_ptr<Command> eqCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Equal>();
    }

    bool eqOp = Interpreter::getInstance().registerCreator(eqCreator, "=");

    std::unique_ptr<Command> lessCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Less>();
    }

    bool lessOp = Interpreter::getInstance().registerCreator(lessCreator, "<");

    std::unique_ptr<Command> greaterCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Greater>();
    }

    bool greaterOp = Interpreter::getInstance().registerCreator(greaterCreator, ">");

    std::unique_ptr<Command> dupCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Dup>();
    }

    bool dupOp = Interpreter::getInstance().registerCreator(dupCreator, "dup");

    std::unique_ptr<Command> dropCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Drop>();
    }

    bool dropOp = Interpreter::getInstance().registerCreator(dropCreator, "drop");

    std::unique_ptr<Command> printCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Print>();
    }

    bool printOp = Interpreter::getInstance().registerCreator(printCreator, ".");

    std::unique_ptr<Command> swapCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Swap>();
    }

    bool swapOp = Interpreter::getInstance().registerCreator(swapCreator, "swap");

    std::unique_ptr<Command> rotCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Rot>();
    }

    bool rotOp = Interpreter::getInstance().registerCreator(rotCreator, "rot");

    std::unique_ptr<Command> overCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Over>();
    }

    bool overOp = Interpreter::getInstance().registerCreator(overCreator, "over");

    std::unique_ptr<Command> emitCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Emit>();
    }

    bool emitOp = Interpreter::getInstance().registerCreator(emitCreator, "emit");

    std::unique_ptr<Command> crCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Cr>();
    }

    bool crOp = Interpreter::getInstance().registerCreator(crCreator, "cr");

    std::unique_ptr<Command> ifCreator(std::string::const_iterator &it, const std::string::const_iterator &end) {
        std::vector<std::unique_ptr<Command>> thenBranch;
        std::vector<std::unique_ptr<Command>> elseBranch;

        auto isIfEnd = [](const std::string &word) { return word == "then" || word == "else"; };

        thenBranch = Interpreter::getInstance().getCommands(it, end, isIfEnd);

        if (it == end) {
            throw interpreter_error("no 'then' for 'if'");
        }

        if (std::string(it, it + 4) == "else") {
            it += 5;
            elseBranch = Interpreter::getInstance().getCommands(it, end, isIfEnd);
        }

        if (it == end) {
            throw interpreter_error("no 'then' for 'if'");
        }

        it += 4;

        if (it == end || it + 1 == end) {
            throw interpreter_error("no ';' for 'if'");
        }

        if (*it != ' ') {
            throw interpreter_error("no ';' for 'if'");
        }

        it++;
        if (*it != ';') {
            throw interpreter_error("no ';' for 'if'");
        }

        it++;

        return std::make_unique<If>(thenBranch, elseBranch);
    }

    bool ifOp = Interpreter::getInstance().registerCreator(ifCreator, "if");

    std::unique_ptr<Command> iCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<I>();
    }

    std::unique_ptr<Command> loopCreator(std::string::const_iterator &it, const std::string::const_iterator &end) {

        Interpreter::getInstance().registerCreator(iCreator, "i");

        auto isLoopEnd = [](const std::string &word) { return word == "loop"; };

        std::vector<std::unique_ptr<Command>> loopBody = Interpreter::getInstance().getCommands(it, end, isLoopEnd);

        if (it == end) {
            throw interpreter_error("no 'loop' for 'do'");
        }

        Interpreter::getInstance().deRegisterCreator("i");

        it += 4;

        if (it == end || it + 1 == end) {
            throw interpreter_error("no ';' for 'loop'");
        }

        if (*it != ' ') {
            throw interpreter_error("no ';' for 'loop'");
        }

        it++;
        if (*it != ';') {
            throw interpreter_error("no ';' for 'loop'");
        }

        it++;

        return std::make_unique<Loop>(loopBody);
    }

    bool loopOp = Interpreter::getInstance().registerCreator(loopCreator, "do");


}