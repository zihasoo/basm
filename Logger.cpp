#include <iostream>

#include "Logger.h"
#include "System.h"

using std::cerr;

void Logger::log_error(pair<int, int> loc, int word_size, const string &msg) {
    buffer.emplace(loc, word_size, msg);
}

void Logger::log_error(const Logger::LogInfo &log_info) {
    buffer.push(log_info);
}

void Logger::register_line(int line_num, const string &line) {
    if (!line_map.contains(line_num))
        line_map.emplace(line_num, line);
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
        auto info = buffer.top();
        buffer.pop();
        cerr << source_name << ' ' << info.raw << ':' << info.col << ": 에러: " << info.msg << '\n';
        cerr.width(5);
        cerr << info.raw << " | " << line_map[info.raw] << '\n'
             << "      | " << indent_by_count(info.col - 1) << "^"
             << tilde(info.word_size - 1) << '\n';
    }
}

bool Logger::has_error() {
    return !buffer.empty();
}

void Logger::set_source(const string &name) {
    source_name = name;
}

