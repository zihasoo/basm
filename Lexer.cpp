#include "Lexer.h"
#include <iostream>

using std::cout;

Lexer::Lexer(const string &file_name) : source(file_name), file_name(file_name) {
    last_word.reserve(30);
}

void Lexer::advance() {
    last_char = source.get();
    if (last_char == '\n' || last_char == '\r') {
        cur_loc.first++;
        cur_loc.second = 1;
    } else {
        cur_loc.second++;
    }
}

Lexer::Token Lexer::get_token() {
    last_word.clear();
    while (isspace(last_char)) {
        advance();
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
    if (op_set.contains(last_char)) {
        advance();
        return tok_op;
    }

    //print_error("undefined token");
    advance();
    return tok_undefined;
}

string Lexer::get_word() {
    return last_word;
}

pair<int, int> Lexer::get_location() {
    return cur_loc;
}

inline string indent_by_digit(int num) {
    string ret;
    while (num) {
        ret.push_back(' ');
        num /= 10;
    }
    return ret;
}

inline string indent_by_count(int count) {
    string ret;
    for (int i = 0; i < count; ++i) {
        ret.push_back(' ');
    }
    return ret;
}

inline string tilde(int count) {
    string ret;
    for (int i = 0; i < count; ++i) {
        ret.push_back('~');
    }
    return ret;
}

void Lexer::print_error(const string &msg) {
    int raw = last_token_loc.first, col = last_token_loc.second;
    cout << file_name << ' ' << raw << ':' << col << ": error: " << msg << '\n'
         << "    " << raw << " | " << last_word << '\n'
         << "    " << indent_by_digit(raw) << " | ^" << tilde(last_word.size() - 1)
         << '\n';
}

void Lexer::print_symbol(Lexer::Token token) {
    cout << file_name << last_token_loc.first << ":" << last_token_loc.second
         << ": token <" << last_word << "> : " << Lexer::token_to_string(token) << '\n';
}

string Lexer::token_to_string(Token token) {
    switch (token) {
        case Lexer::tok_eof:
            return "tok_eof";
        case Lexer::tok_identifier:
            return "tok_identifier";
        case Lexer::tok_int:
            return "tok_int";
        case Lexer::tok_undefined:
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
        case tok_op:
            return "tok_op";
    }
}


