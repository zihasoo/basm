#ifndef BASM_SYSTEM_H
#define BASM_SYSTEM_H

#include <string>
#include <iostream>
#include "Logger.h"

using std::cerr;
using std::string;

class System {

public:
    static string source_name;
    static string output_name;
    static Logger main_logger;

    static void parse_arg(int argc, char **argv);
    static void basm_shutdown();
};


#endif //BASM_SYSTEM_H
