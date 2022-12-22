#pragma once

#include "interpreter_error.h"
#include <sstream>
#include <stack>
#include <cassert>

// CR: data -> data_stack
class data {
public:

    data() = default;

    int pop() {
        assert(!stack_.empty());

        int top = stack_.top();
        stack_.pop();
        return top;
    }

    void expectSize(const unsigned long size, const std::string &cmd) const {
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

    data(data &other) = default;

private:

    std::stack<int> stack_;

    data &operator=(data &other) = delete;

};

struct context {

    context(data & stack): stack(stack) {}

    data &stack;
    std::stringstream out;
    // CR: start -> iteration
    int start = 0;

};
