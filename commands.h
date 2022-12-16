#pragma once

#include "data.h"
#include <functional>
#include <memory>

class Command {
public:

    virtual void apply(context &data) const = 0;

    virtual ~Command() = default;
};

class ParseString : public Command {
public:

    ParseString(std::string str) : content_(std::move(str)) {};

    //prints the string between the quotes
    void apply(context &) const override;

private:
    std::string content_;
};

class PushDigit : public Command {
public:

    PushDigit(int val) : val_(val) {};

    //puts a digit on the top of the stack
    void apply(context &) const override;

private:
    int val_;
};

class BinaryOp : public Command {
public:

    //performs a certain binary operation
    //puts the result on the top of the stack
    void apply(context &) const override;

    virtual int appplyBinOp(int a, int b) const = 0;

};

class Plus : public BinaryOp {
public:

    int appplyBinOp(int a, int b) const override;

};

class Minus : public BinaryOp {
public:

    int appplyBinOp(int a, int b) const override;

};

class Mul : public BinaryOp {
public:

    int appplyBinOp(int a, int b) const override;

};

class Mod : public BinaryOp {
public:

    int appplyBinOp(int a, int b) const override;

};

class Div : public BinaryOp {
public:

    int appplyBinOp(int a, int b) const override;

};

class Less : public BinaryOp {
public:

    int appplyBinOp(int a, int b) const override;

};

class Equal : public BinaryOp {
public:

    int appplyBinOp(int a, int b) const override;

};

class Greater : public BinaryOp {
public:

    int appplyBinOp(int a, int b) const override;

};

class Dup : public Command {
public:

    //copies the top of the stack and pushes it onto the stack
    void apply(context &) const override;
};

class Drop : public Command {
public:

    //pops the top number off the stack
    void apply(context &) const override;
};

class Print : public Command {
public:

    //prints the top number on the stack and pops it off the stack
    void apply(context &) const override;
};

class Swap : public Command {
public:

    //swaps the top and second numbers on the stack
    void apply(context &) const override;
};

class Rot : public Command {
public:

    //rotates the top three numbers on the stack
    void apply(context &) const override;
};

class Over : public Command {
public:

    //copies the second number and places the copy above the top one
    void apply(context &) const override;
};

class Emit : public Command {
public:

    //prints the top number on the stack as an ascii code and pops it off the stack
    void apply(context &) const override;
};


class Cr : public Command {
public:

    //makes a line break
    void apply(context &) const override;
};

class If : public Command {
public:

    If(std::vector<std::unique_ptr<Command>> &thenBranch, std::vector<std::unique_ptr<Command>> &elseBranch)
            : thenBranch_(std::move(thenBranch)),
              elseBranch_(
                      std::move(elseBranch)) {}

    //if there isn't 0 on the top of the stack, the main branch is executed, otherwise else branch
    void apply(context &) const override;

private:
    std::vector<std::unique_ptr<Command>> thenBranch_;
    std::vector<std::unique_ptr<Command>> elseBranch_;
};

class Loop : public Command {
public:

    Loop(std::string &loopBody) : loopBody_(std::move(loopBody)) {}

    void apply(context &) const override;

private:
    std::string loopBody_;

};