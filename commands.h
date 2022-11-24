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

    void apply(data &it, std::stringstream &buf) const override;

};

class Minus : public Command {
public:

    void apply(data &it, std::stringstream &buf) const override;

};

class Mul : public Command {
public:

    void apply(data &it, std::stringstream &buf) const override;

};

class Dev : public Command {
public:

    void apply(data &it, std::stringstream &buf) const override;
};

class Mod : public Command {
public:

    void apply(data &it, std::stringstream &buf) const override;
};

class Equal : public Command {
public:

    void apply(data &it, std::stringstream &buf) const override;
};

class Less : public Command {
public:

    void apply(data &it, std::stringstream &buf) const override;
};

class Greater : public Command {
public:

    void apply(data &it, std::stringstream &buf) const override;
};

class Dup : public Command {
public:

    void apply(data &it, std::stringstream &buf) const override;
};

class Drop : public Command {
public:

    void apply(data &it, std::stringstream &buf) const override;
};

class Print : public Command {
public:

    void apply(data &it, std::stringstream &buf) const override;
};

class Swap : public Command {
public:

    void apply(data &it, std::stringstream &buf) const override;
};

class Rot : public Command {
public:

    void apply(data &it, std::stringstream &buf) const override;
};

class Over : public Command {
public:

    void apply(data &it, std::stringstream &buf) const override;
};

class Emit : public Command {
public:

    void apply(data &it, std::stringstream &buf) const override;
};


class Cr : public Command {
public:

    void apply(data &, std::stringstream &buf) const override;
};

class PrintString : public Command {
public:

    explicit PrintString(std::string str) : str_(std::move(str)) {}

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