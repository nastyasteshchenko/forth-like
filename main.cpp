#include "interpreter.h"
#include <iostream>

int main() {
    Interpreter &i = Interpreter::getInstance();
    while (true) {
        std::cout << "> ";
        std::string str;
        std::getline(std::cin, str);
        const auto res = i.interpret(str.cbegin(), str.cend());
        if (res){
            if (!res.value().empty()) {
                std::cout << "< " << res.value() << std::endl;
            } else {
                std::cout << "< ok" << std::endl;
            }
        }else{
            std::cerr << res.error()<< std::endl;
        }
    }
    return 0;
}