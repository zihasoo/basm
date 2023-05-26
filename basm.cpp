#include "Lexer.h"

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);

    auto lexer = Lexer("test.basm");

    Lexer::Token cur = Lexer::tok_undefined;

    while (cur != Lexer::tok_eof) {
        cur = lexer.get_token();
        lexer.print_error(lexer.token_to_string(cur));
    }

    return 0;
}
