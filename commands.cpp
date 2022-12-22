#include "commands.h"
#include "interpreter_error.h"
#include <sstream>

void PushDigit::apply(context &cntx) const {
    cntx.stack.push(val_);
}

void I::apply(context &cntx) const {
    cntx.stack.push(cntx.start);
}

void ParseString::apply(context &cntx) const {
    cntx.out << content_;
}

void BinaryOp::apply(context &cntx) const {
    cntx.stack.expectSize(2, "binary operation");

    int a = cntx.stack.pop();
    int b = cntx.stack.pop();
    int res = this->applyBinOp(a, b);
    cntx.stack.push(res);
}

int Plus::applyBinOp(const int a, const int b) const {
    return a + b;
}

int Minus::applyBinOp(const int a, const int b) const {
    return b - a;
}

int Mul::applyBinOp(const int a, const int b) const {
    return a * b;
}

int Mod::applyBinOp(const int a, const int b) const {
    if (a == 0) {
        throw interpreter_error("division by zero");
    }
    return b % a;
}

int Div::applyBinOp(const int a, const int b) const {
    if (a == 0) {
        throw interpreter_error("division by zero");
    }
    return b / a;
}

int Less::applyBinOp(const int a, const int b) const {
    return a > b;
}

int Equal::applyBinOp(const int a, const int b) const {
    return a == b;
}

int Greater::applyBinOp(const int a, const int b) const {
    return a < b;
}

void Dup::apply(context &cntx) const {
    cntx.stack.expectSize(1, "dup");

    cntx.stack.push(cntx.stack.top());
}

void Drop::apply(context &cntx) const {
    cntx.stack.expectSize(1, "drop");

    cntx.stack.pop();
}

void Print::apply(context &cntx) const {
    cntx.stack.expectSize(1, ".");

    cntx.out << cntx.stack.top();
    cntx.stack.pop();
}

void Swap::apply(context &cntx) const {
    cntx.stack.expectSize(2, "swap");

    const int tmp1 = cntx.stack.pop();
    const int tmp2 = cntx.stack.top();
    cntx.stack.pop();
    cntx.stack.push(tmp1);
    cntx.stack.push(tmp2);
}

void Rot::apply(context &cntx) const {
    cntx.stack.expectSize(3, "rot");

    const int tmp1 = cntx.stack.pop();
    const int tmp2 = cntx.stack.pop();
    const int tmp3 = cntx.stack.top();

    cntx.stack.pop();
    cntx.stack.push(tmp1);
    cntx.stack.push(tmp3);
    cntx.stack.push(tmp2);
}

void Over::apply(context &cntx) const {
    cntx.stack.expectSize(2, "over");

    const int tmp1 = cntx.stack.pop();
    const int tmp2 = cntx.stack.top();

    cntx.stack.pop();
    cntx.stack.push(tmp2);
    cntx.stack.push(tmp1);
    cntx.stack.push(tmp2);
}

void Emit::apply(context &cntx) const {
    cntx.stack.expectSize(1, "emit");

    cntx.out << (char) cntx.stack.top();
    cntx.stack.pop();
}

void Cr::apply(context &cntx) const {
    cntx.out << std::endl;
}

void If::apply(context &cntx) const {
    cntx.stack.expectSize(1, "if");

    if (cntx.stack.top()) {
        for (auto &cmd: thenBranch_) {
            cmd->apply(cntx);
        }
    } else {
        for (auto &cmd: elseBranch_) {
            cmd->apply(cntx);
        }
    }
}

void Loop::apply(context &cntx) const {
    cntx.stack.expectSize(2, "loop");

    int start = cntx.stack.pop();
    int end = cntx.stack.pop();

    int old = cntx.start;
    cntx.start = start;

    for (int i = start; i < end; i++) {
        for (auto &cmd: loopBody_) {
            cmd->apply(cntx);
        }
        cntx.start= i + 1;
    }

    cntx.start=old;
}