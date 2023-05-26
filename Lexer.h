
#ifndef BASM_LEXER_H
#define BASM_LEXER_H

#include <fstream>
#include <string>
#include <utility>
#include <set>

using std::string;
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

    Lexer();

    Token get_token(); //현재 입력 스트림에서 토큰 타입(enum) 얻기

    string get_word(); //last_word getter

    pair<int, int> get_cur_loc(); //cur_loc getter

    pair<int, int> get_last_loc(); //last_token_loc getter

private:
    string cur_line; //현재 줄

    int last_char = ' '; //마지막으로 읽은 글자

    string last_word; //get_token 함수로부터 얻어진 단어 (string)

    ifstream source; //입력 파일

    pair<int, int> cur_loc = {1, 0}; //row, col. 현재 lexer가 가리키고 있는 위치

    pair<int, int> last_token_loc = {1,0}; //마지막으로 읽은 토큰의 시작 위치

    set<char> op_set = {'$', ',', ';'}; //효력이 있는 특수문자 모음

    void advance(); //현재 입력 스트림에서 한 글자 얻고 위치 기록
};

#endif // BASM_LEXER_H
