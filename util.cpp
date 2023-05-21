#include <iostream>
#include "util.h"

std::string indentByDigit(int num) {
    std::string ret;
    while (num) {
        ret.push_back(' ');
        num /= 10;
    }
    return ret;
}

std::string tilde(int count){
    std::string ret;
    for (int i = 0; i < count; ++i) {
        ret.push_back('~');
    }
    return ret;
}

void logError(const std::pair<int, int> loc, const std::string &symbol, const std::string &msg) {
    std::cout << "test.bs:" << loc.first << ":" << loc.second << ": error: " << msg << '\n'
                 << "    " << loc.first << " | " << symbol << '\n'
                 << "    " << indentByDigit(loc.first) << " | ^" << tilde(symbol.size() - 1) << '\n';
}

void logSymbol(const std::pair<int, int> loc, const std::string &symbol, Lexer::Token token) {
    std::cout << "test.bs:" << loc.first << ":" << loc.second
                 << ": token <" << symbol << "> : " << Lexer::tokenToString(token) << '\n';
}

