
#ifndef BASM_LOGGER_H
#define BASM_LOGGER_H

#include <string>
#include <queue>
#include <map>
#include <utility>
#include <vector>

using std::pair;
using std::string;
using std::priority_queue;
using std::map;

class Logger {
public:
    struct LogInfo {
        int raw, col, word_size;
        string msg;

        LogInfo() = default;

        LogInfo(pair<int,int> loc, int word_size, string msg)
                : raw(loc.first), col(loc.second), word_size(word_size), msg(std::move(msg)) {}

        bool operator>(const LogInfo &other) const {
            if (raw == other.raw) return col > other.col;
            return raw > other.raw;
        }
    };

    void log_error(pair<int, int> loc, int word_size, const string &msg);

    void log_error(const LogInfo &log_info);

    void register_line(int line_num, const string &line);

    void flush();

    bool has_error();

private:
    priority_queue<LogInfo, std::vector<LogInfo>, std::greater<>> buffer;

    map<int, string> line_map;

    static string indent_by_count(int count);

    static string tilde(int count);
};

#endif //BASM_LOGGER_H
