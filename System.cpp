#include "System.h"

string System::source_name = string();
string System::output_name = string();
Logger System::logger = Logger();

void System::parse_arg(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'o' && i + 1 < argc) {
                output_name = argv[++i];
            } else {
                cerr << "에러: 프로그램 인수가 잘못되었습니다.\n";
                exit(1);
            }
        } else {
            source_name = argv[i];
        }
    }
    if (source_name.empty()) {
        cerr << "에러: 소스 파일이 주어지지 않았습니다.\n";
        exit(1);
    }

    if (output_name.empty()) {
        output_name = source_name.substr(0, source_name.find('.') + 1) + "hex";
    }

    logger.set_source(source_name);
}

void System::basm_shutdown() {
    logger.flush();
}
