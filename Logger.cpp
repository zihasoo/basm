#include <iostream>

#include "Logger.h"
#include "System.h"

using std::cerr;

void Logger::log_error(pair<int, int> loc, int word_size, const string &msg) {
    buffer.emplace(loc.first, loc.second, word_size, msg);
}

void Logger::register_line(int line_num, const string &line) {
    if (!line_map.contains(line_num))
        line_map.emplace(line_num, line);
}

string Logger::indent_by_digit(int num) {
    string ret;
    while (num) {
        ret.push_back(' ');
        num /= 10;
    }
    return ret;
}

string Logger::indent_by_count(int count) {
    string ret;
    for (int i = 0; i < count; ++i) {
        ret.push_back(' ');
    }
    return ret;
}

string Logger::tilde(int count) {
    string ret;
    for (int i = 0; i < count; ++i) {
        ret.push_back('~');
    }
    return ret;
}

void Logger::flush() {
    while (!buffer.empty()) {
        auto info = buffer.front();
        if (!line_map.contains(info.raw))
            break;

        buffer.pop();
        cerr << System::source_name << ' ' << info.raw << ':' << info.col << ": 에러: " << info.msg << '\n'
             << "    " << info.raw << " | " << line_map[info.raw] << '\n'
             << "    " << indent_by_digit(info.raw) << " | " << indent_by_count(info.col - 1) << "^"
             << tilde(info.word_size - 1)
             << '\n';
    }
}

