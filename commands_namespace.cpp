#include "commands.h"
#include "interpreter.h"
#include "interpreter_error.h"

namespace {

    std::unique_ptr<Command> addCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Plus>(Plus());
    }

    bool addOp = Interpreter::getInstance().registerCreator(addCreator, "+");

    std::unique_ptr<Command> subCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Minus>(Minus());
    }

    bool subOp = Interpreter::getInstance().registerCreator(subCreator, "-");

    std::unique_ptr<Command> mulCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Mul>(Mul());
    }

    bool mulOp = Interpreter::getInstance().registerCreator(mulCreator, "*");

    std::unique_ptr<Command> devCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Div>(Div());
    }

    bool devOp = Interpreter::getInstance().registerCreator(devCreator, "/");

    std::unique_ptr<Command> modCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Mod>(Mod());
    }

    bool modOp = Interpreter::getInstance().registerCreator(modCreator, "mod");

    std::unique_ptr<Command> eqCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Equal>(Equal());
    }

    bool eqOp = Interpreter::getInstance().registerCreator(eqCreator, "=");

    std::unique_ptr<Command> lessCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Less>(Less());
    }

    bool lessOp = Interpreter::getInstance().registerCreator(lessCreator, "<");

    std::unique_ptr<Command> greaterCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Greater>(Greater());
    }

    bool greaterOp = Interpreter::getInstance().registerCreator(greaterCreator, ">");

    std::unique_ptr<Command> dupCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Dup>(Dup());
    }

    bool dupOp = Interpreter::getInstance().registerCreator(dupCreator, "dup");

    std::unique_ptr<Command> dropCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Drop>(Drop());
    }

    bool dropOp = Interpreter::getInstance().registerCreator(dropCreator, "drop");

    std::unique_ptr<Command> printCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Print>(Print());
    }

    bool printOp = Interpreter::getInstance().registerCreator(printCreator, ".");

    std::unique_ptr<Command> swapCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Swap>(Swap());
    }

    bool swapOp = Interpreter::getInstance().registerCreator(swapCreator, "swap");

    std::unique_ptr<Command> rotCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Rot>(Rot());
    }

    bool rotOp = Interpreter::getInstance().registerCreator(rotCreator, "rot");

    std::unique_ptr<Command> overCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Over>(Over());
    }

    bool overOp = Interpreter::getInstance().registerCreator(overCreator, "over");

    std::unique_ptr<Command> emitCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Emit>(Emit());
    }

    bool emitOp = Interpreter::getInstance().registerCreator(emitCreator, "emit");

    std::unique_ptr<Command> crCreator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Cr>(Cr());
    }

    bool crOp = Interpreter::getInstance().registerCreator(crCreator, "cr");

    std::unique_ptr<Command> ifCreator(std::string::const_iterator &it, const std::string::const_iterator &end) {
        std::vector<std::unique_ptr<Command>> thenBranch;
        std::vector<std::unique_ptr<Command>> elseBranch;

        thenBranch = Interpreter::getInstance().getCommands(it, end);

        if (*it != ';') {
            elseBranch = Interpreter::getInstance().getCommands(it, end);
        }

        it++;

        return std::make_unique<If>(If(thenBranch, elseBranch));
    }

    bool ifOp = Interpreter::getInstance().registerCreator(ifCreator, "if");

    std::unique_ptr<Command> loopCreator(std::string::const_iterator &it, const std::string::const_iterator &end) {
        std::string loopStr = "loop ;";
        auto posLoop = std::find_end(it, end, loopStr.begin(), loopStr.end());
        if (posLoop == end) {
            throw interpreter_error("no 'loop ;' for 'loop'");
        }

        std::string loopBody = std::string(it, --posLoop);
        it = posLoop + 7;

        return std::make_unique<Loop>(Loop(loopBody));
    }

    bool loopOp = Interpreter::getInstance().registerCreator(loopCreator, "do");
}