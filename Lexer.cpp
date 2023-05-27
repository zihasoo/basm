#include "Lexer.h"
#include "Logger.h"
#include "System.h"

Lexer::Lexer(const string& source_name) : source(source_name) {
    last_word.reserve(30);
    cur_line.reserve(80);
    if (!source.is_open()) {
        cerr << "파일이 없거나 잘못되었습니다.";
        exit(1);
    }
}

bool Lexer::advance() {
    last_char = source.get();
    if (last_char == '\n' || last_char == '\r' || last_char == EOF) {
        System::logger.register_line(cur_loc.first, cur_line);
        cur_line.clear();
        cur_loc.first++;
        cur_loc.second = 0;
        return true;
    } else {
        cur_line.push_back(last_char);
        cur_loc.second++;
        return false;
    }
}

void Lexer::release_error(const initializer_list<string> &msg) {
    //매모리의 반복 재할당을 막기 위해 initializer_list로 받고 한 번에 할당
    string str;
    int size = 0;
    for (const auto &x: msg) {
        size += x.size();
    }
    str.reserve(size);
    for (const auto &x: msg) {
        str.append(x);
    }
    System::logger.log_error(last_token_loc, last_word.size(), str);
    while (!advance()); //다음 줄로 이동
}

Lexer::Token Lexer::get_token() {
    last_word.clear();
    while (isspace(last_char)) advance();

    if (last_char == ';') {
        while (!advance()); //주석 나오면 다음 줄까지 계속 이동
        while (isspace(last_char)) advance();
    }

    last_token_loc = cur_loc;
    if (isalpha(last_char)) {
        while (isalnum(last_char)) {
            if (isalpha(last_char)) last_char = tolower(last_char);
            last_word.push_back(last_char);
            advance();
        }
        if (last_word == "nop")
            return tok_nop;
        if (last_word == "add")
            return tok_add;
        if (last_word == "sub")
            return tok_sub;
        if (last_word == "cmp")
            return tok_cmp;
        if (last_word == "ja")
            return tok_ja;
        if (last_word == "jb")
            return tok_jb;
        if (last_word == "je")
            return tok_je;
        if (last_word == "jmp")
            return tok_jmp;
        if (last_word == "mov")
            return tok_mov;

        return tok_identifier;
    }

    if ('0' <= last_char && last_char <= '9') {
        while ('0' <= last_char && last_char <= '9') {
            last_word.push_back(last_char);
            advance();
        }
        return tok_int;
    }

    if (last_char == EOF) {
        return tok_eof;
    }

    last_word.push_back(last_char);
    advance();
    if (last_word == "$") {
        return tok_dollar;
    }
    if (last_word == ";") {
        return tok_semicolon;
    }
    if (last_word == ",") {
        return tok_comma;
    }
    return tok_undefined;
}

const string &Lexer::get_word() {
    return last_word;
}

pair<int, int> Lexer::get_cur_loc() {
    return cur_loc;
}

pair<int, int> Lexer::get_token_loc() {
    return last_token_loc;
}

string Lexer::token_to_string(Token token) {
    switch (token) {
        case tok_eof:
            return "tok_eof";
        case tok_identifier:
            return "tok_identifier";
        case tok_int:
            return "tok_int";
        case tok_undefined:
            return "tok_undefined";
        case tok_data:
            return "tok_data";
        case tok_code:
            return "tok_code";
        case tok_nop:
            return "tok_nop";
        case tok_add:
            return "tok_add";
        case tok_sub:
            return "tok_sub";
        case tok_cmp:
            return "tok_cmp";
        case tok_ja:
            return "tok_ja";
        case tok_jb:
            return "tok_jb";
        case tok_je:
            return "tok_je";
        case tok_jmp:
            return "tok_jmp";
        case tok_mov:
            return "tok_mov";
        case tok_comma:
            return "tok_comma";
        case tok_semicolon:
            return "tok_semicolon";
        case tok_dollar:
            return "tok_dollar";
    }
}
