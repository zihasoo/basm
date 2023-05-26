
#ifndef BASM_LOGGER_H
#define BASM_LOGGER_H

#include <string>
#include <queue>
#include <map>
#include <utility>

using std::pair;
using std::string;
using std::queue;
using std::map;

class Logger {
public:
    void log_error(pair<int,int> loc, int word_size, const string &msg);

    void register_line(int line_num, const string &line);

    void flush();

private:
    struct LogInfo {
        int raw, col, word_size;
        const string msg;

        LogInfo(int raw, int col, int word_size, string msg)
                : raw(raw), col(col), word_size(word_size), msg(std::move(msg)) {}
    };

    queue<LogInfo> buffer;

    map<int,string> line_map;

    static string indent_by_digit(int num);

    static string indent_by_count(int count);

    static string tilde(int count);
};

#endif //BASM_LOGGER_H
