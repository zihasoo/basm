#include "Lexer.h"
#include "util.h"

int main(int argc, char **argv) {

    auto lexer = Lexer("test.bs");

    Lexer::Token cur = Lexer::tok_undefined;

    while (cur != Lexer::tok_eof) {
        cur = lexer.getToken();
        logSymbol(lexer.getLocation(), lexer.getWord(), cur);
    }

    return 0;
}
