#include "System.h"
#include "Lexer.h"
#include "Logger.h"

void test_lexer() {
    Lexer lexer;

    Lexer::Token cur = Lexer::tok_undefined;

    while (cur != Lexer::tok_eof) {
        cur = lexer.get_token();
        System::main_logger.log_error(lexer.get_last_loc(), lexer.get_word().size(),
                          Lexer::token_to_string(cur) + " <" + lexer.get_word() + ">");
    }
}


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    System::parse_arg(argc, argv);

    test_lexer();

    System::basm_shutdown();
    return 0;
}
