#include "System.h"
#include "Lexer.h"
#include "Parser.h"

void test_lexer() {
    Lexer lexer(System::source_name);

    Lexer::Token cur = Lexer::tok_undefined;

    while (cur != Lexer::tok_eof) {
        cur = lexer.get_token();
        System::logger.log_error(lexer.get_token_loc(), lexer.get_word().size(),
                                 Lexer::token_to_string(cur) + " : \"" + lexer.get_word() + "\"");
    }
}


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);

    System::parse_arg(argc, argv);

    Parser parser(System::source_name);

    parser.parse_top_level();
//    parser.show_code();
    parser.write_output();

    System::basm_shutdown();

    return 0;
}
