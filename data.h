#pragma once

#include "interpreter_error.h"
#include <sstream>
#include <stack>

class data {
public:

    data() = default;

    int pop() {
        // CR: assert instead
        if (stack_.empty()) {
            throw interpreter_error("stack has 0 elements, expected 1");
        }

        int top = stack_.top();
        stack_.pop();
        return top;
    }

    // CR: exceptionAboutSize -> expectSize
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

    // CR: remove
    std::stack<int> operator*() const {
        return stack_;
    }

    data(data &other) = default;

private:

    std::stack<int> stack_;

    data &operator=(data &other) = delete;

};

struct range {
    int start;
    int end;
};

struct context {

    data &stack;
    std::stringstream out;
    std::optional<range> loop_range;

};
