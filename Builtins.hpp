#ifndef BUILTINS_HPP
#define BUILTINS_HPP

#include <string>
#include <vector>
#include <algorithm>

#include "Builtin.hpp"
#include "CDBuiltin.hpp"
#include "PWDBuiltin.hpp"
#include "EchoBuiltin.hpp"

class Builtins {
    private:
        CDBuiltin * cd;
        PWDBuiltin * pwd;
        EchoBuiltin * echo;
        vector<string> builtins {
            "cd",
            "pwd",
            "echo"
        };

        void exec(Builtin* builtin, vector<string>args);
    public:
        void exec(string cmd, vector<string> args);
        bool has(string cmd);
};

#endif