#include "commands.h"
#include "interpreter.h"
#include "interpreter_error.h"
#include <algorithm>

namespace {

    std::unique_ptr<Command> add_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Plus>(Plus());
    }

    bool addOp = Interpreter::getInstance().registerCreator(add_creator, "+");

    std::unique_ptr<Command> sub_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Minus>(Minus());
    }

    bool subOp = Interpreter::getInstance().registerCreator(sub_creator, "-");

    std::unique_ptr<Command> mul_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Mul>(Mul());
    }

    bool mulOp = Interpreter::getInstance().registerCreator(mul_creator, "*");

    std::unique_ptr<Command> dev_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Div>(Div());
    }

    bool devOp = Interpreter::getInstance().registerCreator(dev_creator, "/");

    std::unique_ptr<Command> mod_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Mod>(Mod());
    }

    bool modOp = Interpreter::getInstance().registerCreator(mod_creator, "mod");

    std::unique_ptr<Command> eq_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Equal>(Equal());
    }

    bool eqOp = Interpreter::getInstance().registerCreator(eq_creator, "=");

    std::unique_ptr<Command> less_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Less>(Less());
    }

    bool lessOp = Interpreter::getInstance().registerCreator(less_creator, "<");

    std::unique_ptr<Command> greater_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Greater>(Greater());
    }

    bool greaterOp = Interpreter::getInstance().registerCreator(greater_creator, ">");

    std::unique_ptr<Command> dup_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Dup>(Dup());
    }

    bool dupOp = Interpreter::getInstance().registerCreator(dup_creator, "dup");

    std::unique_ptr<Command> drop_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Drop>(Drop());
    }

    bool dropOp = Interpreter::getInstance().registerCreator(drop_creator, "drop");

    std::unique_ptr<Command> print_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Print>(Print());
    }

    bool printOp = Interpreter::getInstance().registerCreator(print_creator, ".");

    std::unique_ptr<Command> swap_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Swap>(Swap());
    }

    bool swapOp = Interpreter::getInstance().registerCreator(swap_creator, "swap");

    std::unique_ptr<Command> rot_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Rot>(Rot());
    }

    bool rotOp = Interpreter::getInstance().registerCreator(rot_creator, "rot");

    std::unique_ptr<Command> over_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Over>(Over());
    }

    bool overOp = Interpreter::getInstance().registerCreator(over_creator, "over");

    std::unique_ptr<Command> emit_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Emit>(Emit());
    }

    bool emitOp = Interpreter::getInstance().registerCreator(emit_creator, "emit");

    std::unique_ptr<Command> cr_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::make_unique<Cr>(Cr());
    }

    bool crOp = Interpreter::getInstance().registerCreator(cr_creator, "cr");

    std::unique_ptr<Command> if_creator(std::string::const_iterator &it, const std::string::const_iterator &end) {
        std::vector<std::unique_ptr<Command>> main_branch;
        std::vector<std::unique_ptr<Command>> else_branch;
        const std::string thenStr = "then ;";
        auto posThen = std::find_end(it, end, thenStr.begin(), thenStr.end());
        if (posThen == end) {
            throw interpreter_error("no 'then ;' for 'if'");
        }
        const std::string elseStr = "else";
        auto posElse = std::find_end(it, end, elseStr.begin(), elseStr.end());
        const std::string ifStr = "if";
        auto posIf = std::find_end(it, end, ifStr.begin(), ifStr.end());
        if (posElse != end && (posIf > posElse || posIf == end || (posThen > posElse && posIf != end))) {
            main_branch = Interpreter::getInstance().getCommands(it, --posElse);
            for (int i = 0; i < 5; i++) {
                ++posElse;
            }

            else_branch = Interpreter::getInstance().getCommands(posElse, --posThen);
        } else {
            main_branch = Interpreter::getInstance().getCommands(it, --posThen);
        }
        for (; *posThen != ';';) {
            ++posThen;
        }
        it = ++posThen;
        return std::make_unique<If>(If(main_branch, else_branch));
    }

    bool ifOp = Interpreter::getInstance().registerCreator(if_creator, "if");
}