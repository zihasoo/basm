
#ifndef BASM_LEXER_H
#define BASM_LEXER_H

#include <fstream>
#include <string>
#include <utility>
#include <set>
#include <map>
#include <initializer_list>
#include "System.h"

using std::string;
using std::ifstream;
using std::pair;
using std::set;
using std::initializer_list;

class Lexer {
public:
    enum Token {
        // commands (opcode랑 값이 같음)
        tok_nop,
        tok_cmp,
        tok_add,
        tok_sub,
        tok_ja,
        tok_jb,
        tok_je,
        tok_jmp,
        tok_mov,

        //eof
        tok_eof,

        // keyword
        tok_data,
        tok_code,

        // primary
        tok_identifier,
        tok_int,

        // operators
        tok_comma,
        tok_semicolon,
        tok_dollar,

        //undefined
        tok_undefined
    };

    Lexer();

    Token get_token(); //현재 입력 스트림에서 토큰 타입(enum) 얻기

    const string& get_word(); //last_word getter

    pair<int, int> get_cur_loc(); //cur_loc getter

    pair<int, int> get_token_loc(); //last_token_loc getter

    void release_error(const initializer_list<string>& msg);

    static string token_to_string(Token token);

private:
    string cur_line; //현재 줄

    int last_char = ' '; //마지막으로 읽은 글자

    string last_word; //get_token 함수로부터 얻어진 단어 (string)

    ifstream source; //입력 파일

    pair<int, int> cur_loc = {1, 0}; //row, col. 현재 lexer가 가리키고 있는 위치

    pair<int, int> last_token_loc = {1, 0}; //마지막으로 읽은 토큰의 시작 위치

    bool advance(); //현재 입력 스트림에서 한 글자 얻고 위치 기록 (줄바꿈 되면 true 리턴)
};

#endif // BASM_LEXER_H
