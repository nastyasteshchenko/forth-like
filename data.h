#pragma once

#include <stack>
#include <iostream>

class data {
public:

    data() = default;

    void pop() {
        stack_.pop();
    }

    int top() {
        return stack_.top();
    }

    void push(int val) {
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
