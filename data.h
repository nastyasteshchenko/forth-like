#pragma once

#include <iostream>
#include <stack>

// CR: merge stack + out
//struct context {
//    data data_;
//    std::stringstream out;
//};

class data {
public:

    data() = default;

    // CR: merge operations like pop and top
    // CR: add exceptions
    void pop() {
        stack_.pop();
    }

    int top() {
        return stack_.top();
    }

    void push(const int val) {
        stack_.push(val);
    }

    size_t size() {
        return stack_.size();
    }

    std::stack<int> operator*() {
        return stack_;
    }

private:

    std::stack<int> stack_;

    data(data &other) = delete;

    data &operator=(data &other) = delete;

};
