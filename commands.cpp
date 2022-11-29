#include "commands.h"
#include "interpreter_error.h"
#include <iostream>
#include <sstream>

void Plus::apply(data &it, std::stringstream &) const {
    if (it.size() == 0) {
        throw interpreter_error("stack have no elements");
    }
    if (it.size() == 1) {
        it.pop();
        throw interpreter_error("stack have only one element");
    }
    int sum = it.top();
    it.pop();
    sum += it.top();
    it.pop();
    it.push(sum);
}

void Minus::apply(data &it, std::stringstream &) const {
    if (it.size() == 0) {
        throw interpreter_error("stack have no elements");
    }
    if (it.size() == 1) {
        it.pop();
        throw interpreter_error("stack have only one element");
    }
    int sub = it.top();
    it.pop();
    sub = it.top() - sub;
    it.pop();
    it.push(sub);
}

void Mul::apply(data &it, std::stringstream &) const {
    if (it.size() == 0) {
        throw interpreter_error("stack have no elements");
    }
    if (it.size() == 1) {
        it.pop();
        throw interpreter_error("stack have only one element");
    }
    int mul = it.top();
    it.pop();
    mul *= it.top();
    it.pop();
    it.push(mul);
}

// CR:
// BinaryOp: Command
// std::function

// CR: Dev -> Div
void Dev::apply(data &it, std::stringstream &) const {
    if (it.size() == 0) {
        throw interpreter_error("stack have no elements");
    }
    if (it.size() == 1) {
        it.pop();
        throw interpreter_error("stack have only one element");
    }
    int dev = it.top();
    it.pop();
    if (dev == 0) {
        it.pop();
        throw interpreter_error("division by zero");
    }
    dev = it.top() / dev;
    it.pop();
    it.push(dev);
}

void Mod::apply(data &it, std::stringstream &) const {
    if (it.size() == 0) {
        throw interpreter_error("stack have no elements");
    }
    if (it.size() == 1) {
        it.pop();
        throw interpreter_error("stack have only one element");
    }
    int mod = it.top();
    it.pop();
    mod = it.top() % mod;
    it.pop();
    it.push(mod);
}

void Equal::apply(data &it, std::stringstream &) const {
    if (it.size() == 0) {
        throw interpreter_error("stack have no elements");
    }
    if (it.size() == 1) {
        it.pop();
        throw interpreter_error("stack have only one element");
    }
    const int eq = it.top();
    it.pop();
    if (eq == it.top()){
        it.pop();
        it.push(1);
    } else {
        it.pop();
        it.push(0);
    }
}

void Less::apply(data &it, std::stringstream &) const {
    if (it.size() == 0) {
        throw interpreter_error("stack have no elements");
    }
    if (it.size() == 1) {
        it.pop();
        throw interpreter_error("stack have only one element");
    }
    const int eq = it.top();
    it.pop();
    if (eq > it.top()){
        it.pop();
        it.push(1);
    } else {
        it.pop();
        it.push(0);
    }
}

void Greater::apply(data &it, std::stringstream &) const {
    if (it.size() == 0) {
        throw interpreter_error("stack have no elements");
    }
    if (it.size() == 1) {
        it.pop();
        throw interpreter_error("stack have only one element");
    }
    const int eq = it.top();
    it.pop();
    if (eq < it.top()){
        it.pop();
        it.push(1);
    } else {
        it.pop();
        it.push(0);
    }
}

void Dup::apply(data &it, std::stringstream &) const {
    if (it.size() == 0) {
        throw interpreter_error("stack have no elements");
    }
    it.push(it.top());
}

void Drop::apply(data &it, std::stringstream &) const {
    if (it.size() == 0) {
        throw interpreter_error("stack has no elements");
    }
    it.pop();
}

void Print::apply(data &it, std::stringstream &buf) const {
    if (it.size() == 0) {
        throw interpreter_error("stack have no elements");
    }
    buf << it.top();
    it.pop();
}

void Swap::apply(data &it, std::stringstream &) const {
    if (it.size() == 0) {
        throw interpreter_error("stack have no elements");
    }
    if (it.size() == 1) {
        throw interpreter_error("stack have only one element");
    }
    const int tmp1 = it.top();
    it.pop();
    const int tmp2 = it.top();
    it.pop();
    it.push(tmp1);
    it.push(tmp2);
}

void Rot::apply(data &it, std::stringstream &) const {
    if (it.size() == 0) {
        throw interpreter_error("stack have no elements");
    }
    if (it.size() == 1) {
        throw interpreter_error("stack have only one element");
    }
    if (it.size() == 2) {
        throw interpreter_error("stack have only two elements");
    }
//    if (it.size() < 3) {
//        throw interpreter_error("stack has '" std::string(), "expected ...")
//    }
    const int tmp1 = it.top();
    it.pop();
    const int tmp2 = it.top();
    it.pop();
    const int tmp3 = it.top();
    it.pop();
    it.push(tmp1);
    it.push(tmp3);
    it.push(tmp2);
}

void Over::apply(data &it, std::stringstream &) const {
    if (it.size() == 0) {
        throw interpreter_error("stack have no elements");
    }
    if (it.size() == 1) {
        throw interpreter_error("stack have only one element");
    }
    const int tmp1 = it.top();
    it.pop();
    const int tmp2 = it.top();
    it.pop();
    it.push(tmp2);
    it.push(tmp1);
    it.push(tmp2);
}

void Emit::apply(data &it, std::stringstream &buf) const {
    if (it.size() == 0) {
        throw interpreter_error("stack have no elements");
    }
    buf << (char) it.top();
    it.pop();
}

void Cr::apply(data &, std::stringstream &buf) const {
    buf << std::endl;
}

void PrintString::apply(data &, std::stringstream &buf) const {
    buf << str_;
}
