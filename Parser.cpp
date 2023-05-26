#include <fstream>
#include <bitset>
#include <iostream>

#include "Parser.h"

Parser::Parser() {
    result.reserve(60);
}

void Parser::parse_top_level() {
    Lexer::Token token = Lexer::tok_undefined;
    while (true) {
        token = lexer.get_token();
        if (token == Lexer::tok_eof) break;

        if (token == Lexer::tok_undefined) { //error
            lexer.release_error({"알 수 없는 토큰: \"", lexer.get_word(), "\""});
        } else if (token == Lexer::tok_comma || token == Lexer::tok_identifier || token == Lexer::tok_int) {
            lexer.release_error({"잘못된 토큰: \"", lexer.get_word(), "\" 해당 토큰은 여기에 올 수 없습니다."});
        } else if (token == Lexer::tok_dollar) { //label
            parse_label();
        } else if (token == Lexer::tok_nop) { //nop
            result.push_back(0);
        } else if (token & (1 << 2)) { //ja, jb, je, jmp (피연산자 한 개)
            parse_jmp(token);
        } else { //나머지 모든 명령어 (피연산자 두 개)
            parse_command(token);
        }
    }
    set_unregistered_label(); //라벨들 처리
}

bool Parser::is_proper_regi(const string &regi_name) {
    if (regi_name.size() == 1 && 'a' <= regi_name[0] && regi_name[0] <= 'c') {
        return true;
    }
    lexer.release_error({"\"", regi_name, "\"는 잘못된 레지스터명입니다. 레지스터는 A,B,C 중 하나여야 합니다."});
    return false;
}

void Parser::parse_label() {
    auto token = lexer.get_token();
    if (token != Lexer::tok_identifier) {
        lexer.release_error({"잘못된 토큰: \"", lexer.get_word(),
                             "\" 라벨명은 다른 명령어 이름이 아니어야 하고, 숫자로 시작하지 않아야 합니다."});
        return;
    }
    if (label_map.contains(lexer.get_word())) {
        lexer.release_error({"이미 선언된 라벨입니다."});
        return;
    }
    label_map.emplace(lexer.get_word(), result.size());
}


void Parser::parse_jmp(Lexer::Token token) {
    result.push_back((token << 4) + 3); //jmp들은 항상 src가 imm이어야해서 + 3을 하는 것
    token = lexer.get_token(); //라벨 파싱
    if (token != lexer.tok_identifier) {
        lexer.release_error({"잘못된 토큰: \"", lexer.get_word(), "\" 라벨이 필요합니다."});
    }
    if (label_map.contains(lexer.get_word())) { //등록된 라벨이면 바로 값 대입
        result.push_back(label_map[lexer.get_word()]);
    } else {
        //등록되지 않은 라벨 기록
        unregistered_label_map.emplace(result.size(), Logger::LogInfo(lexer.get_token_loc(), lexer.get_word().size(),
                                                                      lexer.get_word()));
        result.push_back(-1);
    }
}

void Parser::parse_command(Lexer::Token token) {
    auto command = token;

    token = lexer.get_token();
    if (token == Lexer::tok_int) {
        lexer.release_error({"dest는 즉시값이 될 수 없습니다."});
        return;
    }
    if (!is_proper_regi(lexer.get_word())) return;
    char dest = lexer.get_word()[0];

    token = lexer.get_token();
    if (token != Lexer::tok_comma) {
        lexer.release_error({"잘못된 토큰: \"", lexer.get_word(), "\" 이곳엔 콤마가 와야 합니다."});
        return;
    }

    token = lexer.get_token();
    if (token == Lexer::tok_identifier) {
        if (!is_proper_regi(lexer.get_word())) return;
        result.push_back((command << 4) + ((dest - 'a') << 2) + (lexer.get_word()[0] - 'a'));
    } else if (token == Lexer::tok_int) {
        int val = std::stoi(lexer.get_word());
        if (val > 255) {
            lexer.release_error({"즉시값은 255이하여야 합니다."});
            return;
        }
        result.push_back((command << 4) + ((dest - 'a') << 2) + 3);
        result.push_back(val);
    } else {
        lexer.release_error({"잘못된 토큰: \"", lexer.get_word(), "\" src에는 값 또는 레지스터가 와야 합니다."});
    }
}

void Parser::set_unregistered_label() {
    for (int i = 0; i < result.size(); ++i) {
        if (result[i] == -1) {
            if (!label_map.contains(unregistered_label_map[i].msg)) {
                auto info = unregistered_label_map[i];
                info.msg = "라벨 \"" + info.msg + "\"는 존재하지 않는 라벨입니다.";
                System::logger.log_error(info);
            } else {
                result[i] = label_map[unregistered_label_map[i].msg];
            }
        }
    }
}

void Parser::show_code() {
    if (System::logger.has_error()) return;

    for (int op: result) {
        string res = std::bitset<8>(op).to_string();
        std::cout << res.substr(0, 4) << ' ' << res.substr(4, 4) << '\n';
    }
}

void Parser::write_output() {
    if (System::logger.has_error()) return;

    std::ofstream output(System::output_name);
    output << "v3.0 hex words plain\n";

    for (int i = 0; i < result.size(); ++i) {
        output.width(2);
        output.fill('0');
        output << std::hex << result[i] << ' ';
        if (i % 10 == 9) output << '\n';
    }
}
