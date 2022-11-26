#pragma once

#include "data.h"
#include <iostream>

class Command {
public:

    virtual void apply(data &, std::stringstream &buf) const = 0;

    virtual ~Command() = default;
};

class Plus : public Command {
public:

    //sums the top and second numbers on the stack
    //numbers are popped off the stack, the result is pushed onto the top of the stack
    void apply(data &it, std::stringstream &buf) const override;

};

class Minus : public Command {
public:

    //subtracts the number at the top of the stack from the second number on the stack
    //numbers are popped off the stack, the result is pushed onto the top of the stack
    void apply(data &it, std::stringstream &buf) const override;

};

class Mul : public Command {
public:

    //multiplies the top and second numbers on the stack
    //numbers are popped off the stack, the result is pushed onto the top of the stack
    void apply(data &it, std::stringstream &buf) const override;

};

class Dev : public Command {
public:

    //divides the second number on the stack by the number at the top of the stack
    //numbers are popped off the stack, the result is pushed onto the top of the stack
    void apply(data &it, std::stringstream &buf) const override;
};

class Mod : public Command {
public:

    //calculates the remainder of a division the second number on the stack by the number at the top of the stack
    //numbers are popped off the stack, the result is pushed onto the top of the stack
    void apply(data &it, std::stringstream &buf) const override;
};

class Equal : public Command {
public:

    //if the top and second numbers on the stack are equal, 1 is pushed onto the top of the stack
    //if the top and second numbers on the stack aren't equal, 0 is pushed onto the top of the stack
    void apply(data &it, std::stringstream &buf) const override;
};

class Less : public Command {
public:

    //if the second number on the stack is less than the number at the top of the stack, 1 is pushed onto the top of the stack
    //if the second number on the stack isn't less than the number at the top of the stack, 0 is pushed onto the top of the stack
    void apply(data &it, std::stringstream &buf) const override;
};

class Greater : public Command {
public:

    //if the second number on the stack is greater than the number at the top of the stack, 1 is pushed onto the top of the stack
    //if the second number on the stack isn't greater than the number at the top of the stack, 0 is pushed onto the top of the stack
    void apply(data &it, std::stringstream &buf) const override;
};

class Dup : public Command {
public:

    //copies the top of the stack and pushes it onto the stack
    void apply(data &it, std::stringstream &buf) const override;
};

class Drop : public Command {
public:

    //pops the top number off the stack
    void apply(data &it, std::stringstream &buf) const override;
};

class Print : public Command {
public:

    //prints the top number on the stack and pops it off the stack
    void apply(data &it, std::stringstream &buf) const override;
};

class Swap : public Command {
public:

    //swaps the top and second numbers on the stack
    void apply(data &it, std::stringstream &buf) const override;
};

class Rot : public Command {
public:

    //rotates the top three numbers on the stack
    void apply(data &it, std::stringstream &buf) const override;
};

class Over : public Command {
public:

    //copies the second number and places the copy above the top one
    void apply(data &it, std::stringstream &buf) const override;
};

class Emit : public Command {
public:

    //prints the top number on the stack as an ascii code and pops it off the stack
    void apply(data &it, std::stringstream &buf) const override;
};


class Cr : public Command {
public:

    //makes a line break
    void apply(data &, std::stringstream &buf) const override;
};

class PrintString : public Command {
public:

    explicit PrintString(std::string str) : str_(std::move(str)) {}

    //prints a string between quotes
    void apply(data &, std::stringstream &buf) const override;

private:
    std::string str_;
};

class If : public Command {
public:

    void apply(data &, std::stringstream &) const override{}

};

class Then : public Command {
public:

    void apply(data &, std::stringstream &) const override{}

};

class Else : public Command {
public:

    void apply(data &, std::stringstream &) const override{}

};