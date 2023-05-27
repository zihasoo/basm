#ifndef BASM_PARSER_H
#define BASM_PARSER_H

#include <vector>
#include <map>
#include <queue>

#include "Lexer.h"
#include "System.h"

using std::vector;
using std::queue;
using std::map;

class Parser {
public:
    Parser(const string& source_name);

    void parse_top_level(); //최상위 파싱. 어떤 구문인지 먼저 판단

    void write_output(); //파싱 결과로 코드 생성

    void show_code(); //opcode를 표준 출력에 출력

private:
    Lexer lexer;

    vector<int> result; //어셈블 결과 (바이너리)

    map<string, int> label_map; //라벨 - 주소값 맵

    map<int, Logger::LogInfo> unregistered_label_map; //라벨 사용 위치 - 라벨 이름 + 에러메시지용 정보
    // (파싱할 당시에 등록되지 않은 라벨을 사용한 경우 여기에 저장함)

    void parse_label(); //라벨 선언 파싱

    void parse_jmp(Lexer::Token token); //점프 구문 파싱

    void parse_command(Lexer::Token token); //이외 명령어 구문 파싱

    bool is_proper_regi(const string &regi_name); //레지스터 이름이 적합한지 판단

    void set_unregistered_label(); //사용보다 선언이 뒤에 온 라벨들 처리

};

#endif //BASM_PARSER_H
