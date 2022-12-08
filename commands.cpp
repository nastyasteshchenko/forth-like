#include "commands.h"
#include "interpreter_error.h"
#include <iostream>
#include <sstream>
#include <functional>

void ParseDigit::apply(context &cntx) const {
    cntx.stack.push(val_);
}

void ParseString::apply(context &cntx) const {
    auto it = std::find_if(str_.begin(), str_.end(), [](char c) { return c == '\"'; });
    const auto end = std::find_if(++it, str_.end(), [](char c) { return c == '\"'; });
    if (end == str_.end()) {
        throw interpreter_error("no closing quotation mark for printing string");
    }
    for (auto iter = it; *iter != '\"'; iter++) {
        cntx.out << *iter;
    }
}

void BinaryOp::apply(context &cntx) const {
    cntx.stack.exceptionAboutSize(2, "binary operation");
    int a = cntx.stack.pop();
    int b = cntx.stack.pop();
    int res = this->appplyBinOp(a, b);
    cntx.stack.push(res);
}

int Plus::appplyBinOp(const int a, const int b) const {
    return a + b;
}

int Minus::appplyBinOp(const int a, const int b) const {
    return b - a;
}

int Mul::appplyBinOp(const int a, const int b) const {
    return a * b;
}

int Mod::appplyBinOp(const int a, const int b) const {
    return b % a;
}

int Div::appplyBinOp(const int a, const int b) const {
    if (a == 0) {
        throw interpreter_error("division by zero");
    }
    return b / a;
}

int Less::appplyBinOp(const int a, const int b) const {
    return a > b;
}

int Equal::appplyBinOp(const int a, const int b) const {
    return a == b;
}

int Greater::appplyBinOp(const int a, const int b) const {
    return a < b;
}

void Dup::apply(context &cntx) const {
    cntx.stack.exceptionAboutSize(1, "dup");
    cntx.stack.push(cntx.stack.top());
}

void Drop::apply(context &cntx) const {
    cntx.stack.exceptionAboutSize(1, "drop");
    cntx.stack.pop();
}

void Print::apply(context &cntx) const {
    cntx.stack.exceptionAboutSize(1, ".");
    cntx.out << std::to_string(cntx.stack.top()).c_str();
    cntx.stack.pop();
}

void Swap::apply(context &cntx) const {
    cntx.stack.exceptionAboutSize(2, "swap");
    const int tmp1 = cntx.stack.pop();
    const int tmp2 = cntx.stack.top();
    cntx.stack.pushInsteadOfTop(tmp1);
    cntx.stack.push(tmp2);
}

void Rot::apply(context &cntx) const {
    cntx.stack.exceptionAboutSize(3, "rot");
    const int tmp1 = cntx.stack.pop();
    const int tmp2 = cntx.stack.pop();
    const int tmp3 = cntx.stack.top();
    cntx.stack.pushInsteadOfTop(tmp1);
    cntx.stack.push(tmp3);
    cntx.stack.push(tmp2);
}

void Over::apply(context &cntx) const {
    cntx.stack.exceptionAboutSize(2, "over");
    const int tmp1 = cntx.stack.pop();
    const int tmp2 = cntx.stack.top();
    cntx.stack.pushInsteadOfTop(tmp2);
    cntx.stack.push(tmp1);
    cntx.stack.push(tmp2);
}

void Emit::apply(context &cntx) const {
    cntx.stack.exceptionAboutSize(1, "emit");
    cntx.out << (char) cntx.stack.top();
    cntx.stack.pop();
}

void Cr::apply(context &cntx) const {
    cntx.out << std::endl;
}

void If::apply(context &cntx) const {
    cntx.stack.exceptionAboutSize(1, "if");
    if (cntx.stack.top()) {
        for (auto &cmd: main_branch_) {
            cmd->apply(cntx);
        }
    } else {
        for (auto &cmd: else_branch_) {
            cmd->apply(cntx);
        }
    }
}