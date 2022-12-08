#pragma once

#include "interpreter_error.h"
#include <sstream>
#include <stack>

class data {
public:

    data() = default;

    void pushInsteadOfTop(const int val) {
        stack_.pop();
        stack_.push(val);
    }

    int pop() {
        int top = stack_.top();
        stack_.pop();
        return top;
    }

    void exceptionAboutSize(const unsigned long size, const std::string &cmd) const {
        if (stack_.size() < size) {
            std::stringstream ss;
            ss << "stack has " << stack_.size() << " elements, expected " << size << " for '" << cmd << "'";
            throw interpreter_error(ss.str());
        }
    }


    int top() const {
        return stack_.top();
    }

    void push(const int val) {
        stack_.push(val);
    }

    size_t size() const {
        return stack_.size();
    }

    std::stack<int> operator*() const {
        return stack_;
    }

private:

    std::stack<int> stack_;

    data(data &other) = delete;

    data &operator=(data &other) = delete;

};

struct context {

    data stack;
    std::stringstream out;

};
