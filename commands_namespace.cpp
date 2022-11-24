#include "commands.h"
#include "interpreter.h"
#include "interpreter_error.h"
#include <algorithm>

namespace {

    SmartPointer<Command> add_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return new Plus();
    }

    bool addOp = Interpreter::getInstance().registerCreator(add_creator, "+");

    SmartPointer<Command> sub_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return new Minus();
    }

    bool subOp = Interpreter::getInstance().registerCreator(sub_creator, "-");

    SmartPointer<Command> mul_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return new Mul();
    }

    bool mulOp = Interpreter::getInstance().registerCreator(mul_creator, "*");

    SmartPointer<Command> dev_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return new Dev();
    }

    bool devOp = Interpreter::getInstance().registerCreator(dev_creator, "/");

    SmartPointer<Command> mod_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return new Mod();
    }

    bool modOp = Interpreter::getInstance().registerCreator(mod_creator, "mod");

    SmartPointer<Command> eq_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return new Equal();
    }

    bool eqOp = Interpreter::getInstance().registerCreator(eq_creator, "=");

    SmartPointer<Command> less_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return new Less();
    }

    bool lessOp = Interpreter::getInstance().registerCreator(less_creator, "<");

    SmartPointer<Command> greater_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return new Greater();
    }

    bool greaterOp = Interpreter::getInstance().registerCreator(greater_creator, ">");

    SmartPointer<Command> dup_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return new Dup();
    }

    bool dupOp = Interpreter::getInstance().registerCreator(dup_creator, "dup");

    SmartPointer<Command> drop_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return new Drop();
    }

    bool dropOp = Interpreter::getInstance().registerCreator(drop_creator, "drop");

    SmartPointer<Command> print_creator(std::string::const_iterator &it, const std::string::const_iterator &end) {
        if (*it == '\"') {
            it++;
            auto cl_quote_it = std::find_if(it, end, [](char c) { return c == '"'; });
            if (cl_quote_it == end) {
                throw interpreter_error("no closing quotation mark for print string");
            }
            std::stringstream ss;
            for (; it != cl_quote_it; it++) {
                ss << *it;
            }
            return new PrintString(ss.str());
        }
        return new Print();
    }

    bool printOp = Interpreter::getInstance().registerCreator(print_creator, ".");

    SmartPointer<Command> swap_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return new Swap();
    }

    bool swapOp = Interpreter::getInstance().registerCreator(swap_creator, "swap");

    SmartPointer<Command> rot_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return new Rot();
    }

    bool rotOp = Interpreter::getInstance().registerCreator(rot_creator, "rot");

    SmartPointer<Command> over_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return new Over();
    }

    bool overOp = Interpreter::getInstance().registerCreator(over_creator, "over");

    SmartPointer<Command> emit_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return new Emit();
    }

    bool emitOp = Interpreter::getInstance().registerCreator(emit_creator, "emit");

    SmartPointer<Command> cr_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return new Cr();
    }

    bool crOp = Interpreter::getInstance().registerCreator(cr_creator, "cr");

    SmartPointer<Command> if_creator(std::string::const_iterator &it, const std::string::const_iterator &end) {
        const auto colon_it = std::find_if(it, end, [](char c) { return c == ';'; });
        if (colon_it == end) {
            throw interpreter_error("no colon for 'if'");
        }
        auto else_it = std::find_if(it, end, [](char c) { return c == 'e'; });
        std::stringstream ss;
        auto iter = else_it;
        ss << *iter << *(++iter) << *(++iter) << *(++iter);
        it++;
        if (Interpreter::getInstance().operator*().top() != 0) {
            if (ss.str() == "else") {
                Interpreter::getInstance().getAndApplyCommands(it, else_it);
            } else {
                Interpreter::getInstance().getAndApplyCommands(it, colon_it);
            }
        }
        if (ss.str() == "else") {
            else_it--;
            it = else_it;
        } else {
            it = colon_it;
        }
        return new If();
    }

    bool ifOp = Interpreter::getInstance().registerCreator(if_creator, "if");

    SmartPointer<Command> then_creator(std::string::const_iterator &, const std::string::const_iterator &) {
        return new Then();
    }

    bool thenOp = Interpreter::getInstance().registerCreator(then_creator, "then;");

    SmartPointer<Command> else_creator(std::string::const_iterator &it, const std::string::const_iterator &end) {
        const auto colon_it = std::find_if(it, end, [](char c) { return c == ';'; });
        if (colon_it == end) {
            throw interpreter_error("no colon for 'if'");
        }
        it++;
        if (Interpreter::getInstance().operator*().top() == 0)
            Interpreter::getInstance().getAndApplyCommands(it, colon_it);
        it = colon_it;
        return new Else();
    }

    bool elseOp = Interpreter::getInstance().registerCreator(else_creator, "else");
}