
#ifndef BASM_LEXER_H
#define BASM_LEXER_H

#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <set>

using std::string;
using std::vector;
using std::ifstream;
using std::pair;
using std::set;

class Lexer {
public:
    enum Token {
        tok_eof,

        // keyword
        tok_data,
        tok_code,

        // primary
        tok_identifier,
        tok_int,

        // commands
        tok_nop,
        tok_add,
        tok_sub,
        tok_cmp,
        tok_ja,
        tok_jb,
        tok_je,
        tok_jmp,
        tok_mov,

        // operators
        tok_op,

        //undefined
        tok_undefined
    };

    static string token_to_string(Token token);

    explicit Lexer(const string &file_name);

    Token get_token(); //현재 입력 스트림에서 토큰 타입(enum) 얻기

    string get_word(); //get_token 함수로부터 얻어진 단어 (string) 반환

    pair<int, int> get_location();

    void print_symbol(Lexer::Token token);

    void print_error(const string &msg);

private:
    string file_name;
    int last_char = ' ';
    string last_word;
    ifstream source;
    pair<int, int> cur_loc = {1, 1}; //row, col
    pair<int, int> last_token_loc = {1,1};
    set<char> op_set = {'[', ']', '$', '.', ',', ':', ';', '\"', '\''};

    void advance(); //현재 입력 스트림에서 한 글자 얻고 위치 기록
};

#endif // BASM_LEXER_H
