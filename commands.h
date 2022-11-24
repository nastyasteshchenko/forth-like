#pragma once

#include "data.h"

class Command {
public:

    virtual void apply(data &) const = 0;

    virtual ~Command() = default;
};

class Plus : public Command {
public:

    void apply(data &it) const override;

};

class Minus : public Command {
public:

    void apply(data &it) const override;

};

class Mul : public Command {
public:

    void apply(data &it) const override;

};

class Dev : public Command {
public:

    void apply(data &it) const override;
};

class Mod : public Command {
public:

    void apply(data &it) const override;
};

class Equal : public Command {
public:

    void apply(data &it) const override;
};

class Less : public Command {
public:

    void apply(data &it) const override;
};

class Greater : public Command {
public:

    void apply(data &it) const override;
};

class Dup : public Command {
public:

    void apply(data &it) const override;
};

class Drop : public Command {
public:

    void apply(data &it) const override;
};

class Print : public Command {
public:

    void apply(data &it) const override;
};

class Swap : public Command {
public:

    void apply(data &it) const override;
};

class Rot : public Command {
public:

    void apply(data &it) const override;
};

class Over : public Command {
public:

    void apply(data &it) const override;
};

class Emit : public Command {
public:

    void apply(data &it) const override;
};


class Cr : public Command {
public:

    void apply(data &) const override;
};

class PrintString : public Command {
public:

    explicit PrintString(std::string str) : str_(std::move(str)) {}

    void apply(data &) const override;

private:
    std::string str_;
};

class If : public Command {
public:

    void apply(data &) const override {}

};

class Then : public Command {
public:

    void apply(data &) const override {}

};

class Else : public Command {
public:

    void apply(data &) const override {}

};