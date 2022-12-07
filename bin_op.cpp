#include "bin_op.h"
#include "interpreter_error.h"

void plus(context &cntx) {
    const int tmp = cntx.stack.getAndPopTopValue();
    cntx.stack.pushInsteadOfTop(tmp + cntx.stack.top());
}

void minus(context &cntx) {
    const int tmp = cntx.stack.getAndPopTopValue();
    cntx.stack.pushInsteadOfTop(cntx.stack.top() - tmp);
}

void mul(context &cntx) {
    const int tmp = cntx.stack.getAndPopTopValue();
    cntx.stack.pushInsteadOfTop(cntx.stack.top() * tmp);
}

void division(context &cntx) {
    const int tmp = cntx.stack.getAndPopTopValue();
    if (tmp == 0) {
        throw interpreter_error("division by zero");
    }
    cntx.stack.pushInsteadOfTop(cntx.stack.top() / tmp);
}

void mod(context &cntx) {
    const int tmp = cntx.stack.getAndPopTopValue();
    cntx.stack.pushInsteadOfTop(cntx.stack.top() % tmp);
}

void equal(context &cntx) {
    const int tmp = cntx.stack.getAndPopTopValue();
    cntx.stack.pushInsteadOfTop(cntx.stack.top() == tmp);
}

void less(context &cntx) {
    const int tmp = cntx.stack.getAndPopTopValue();
    cntx.stack.pushInsteadOfTop(cntx.stack.top() < tmp);
}

void greater(context &cntx) {
    const int tmp = cntx.stack.getAndPopTopValue();
    cntx.stack.pushInsteadOfTop(cntx.stack.top() > tmp);
}