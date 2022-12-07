#include "commands.h"
#include "interpreter.h"
#include "interpreter_error.h"
#include <algorithm>

namespace {

    std::unique_ptr<Command> add_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::unique_ptr<Command>(new BinaryOp("+"));
    }

    bool addOp = Interpreter::getInstance().registerCreator(add_creator, "+");

    std::unique_ptr<Command> sub_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::unique_ptr<Command>(new BinaryOp("-"));
    }

    bool subOp = Interpreter::getInstance().registerCreator(sub_creator, "-");

    std::unique_ptr<Command> mul_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::unique_ptr<Command>(new BinaryOp("*"));
    }

    bool mulOp = Interpreter::getInstance().registerCreator(mul_creator, "*");

    std::unique_ptr<Command> dev_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::unique_ptr<Command>(new BinaryOp("/"));
    }

    bool devOp = Interpreter::getInstance().registerCreator(dev_creator, "/");

    std::unique_ptr<Command> mod_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::unique_ptr<Command>(new BinaryOp("mod"));
    }

    bool modOp = Interpreter::getInstance().registerCreator(mod_creator, "mod");

    std::unique_ptr<Command> eq_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::unique_ptr<Command>(new BinaryOp("="));
    }

    bool eqOp = Interpreter::getInstance().registerCreator(eq_creator, "=");

    std::unique_ptr<Command> less_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::unique_ptr<Command>(new BinaryOp("<"));
    }

    bool lessOp = Interpreter::getInstance().registerCreator(less_creator, "<");

    std::unique_ptr<Command> greater_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::unique_ptr<Command>(new BinaryOp(">"));
    }

    bool greaterOp = Interpreter::getInstance().registerCreator(greater_creator, ">");

    std::unique_ptr<Command> dup_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::unique_ptr<Command>(new Dup());
    }

    bool dupOp = Interpreter::getInstance().registerCreator(dup_creator, "dup");

    std::unique_ptr<Command> drop_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::unique_ptr<Command>(new Drop());
    }

    bool dropOp = Interpreter::getInstance().registerCreator(drop_creator, "drop");

    std::unique_ptr<Command> print_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::unique_ptr<Command>(new Print());
    }

    bool printOp = Interpreter::getInstance().registerCreator(print_creator, ".");

    std::unique_ptr<Command> swap_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::unique_ptr<Command>(new Swap());
    }

    bool swapOp = Interpreter::getInstance().registerCreator(swap_creator, "swap");

    std::unique_ptr<Command> rot_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::unique_ptr<Command>(new Rot());
    }

    bool rotOp = Interpreter::getInstance().registerCreator(rot_creator, "rot");

    std::unique_ptr<Command> over_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::unique_ptr<Command>(new Over());
    }

    bool overOp = Interpreter::getInstance().registerCreator(over_creator, "over");

    std::unique_ptr<Command> emit_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::unique_ptr<Command>(new Emit());
    }

    bool emitOp = Interpreter::getInstance().registerCreator(emit_creator, "emit");

    std::unique_ptr<Command> cr_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return std::unique_ptr<Command>(new Cr());
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
        if (posElse != end && (posIf > posElse || posIf == end  || (posThen>posElse && posIf!=end ))){
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
        return std::unique_ptr<Command>(new If(main_branch, else_branch));
    }

    bool ifOp = Interpreter::getInstance().registerCreator(if_creator, "if");
}