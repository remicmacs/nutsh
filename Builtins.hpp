#ifndef BUILTINS_HPP
#define BUILTINS_HPP

#include <string>
#include <vector>
#include <algorithm>

#include "Builtin.hpp"
#include "CDBuiltin.hpp"
#include "PWDBuiltin.hpp"

class Builtins {
    private:
        CDBuiltin * cd;
        PWDBuiltin * pwd;
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