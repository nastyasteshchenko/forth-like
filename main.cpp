#include "interpreter.h"

int main() {
    Interpreter &i = Interpreter::getInstance();
    while (true) {
        std::cout << "> ";
        std::string tmpStr;
        std::getline(std::cin, tmpStr);
        std::string str = tmpStr;
        i.interpret(str.cbegin(), str.cend());
    }
    return 0;
}