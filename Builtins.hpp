#ifndef BUILTINS_HPP
#define BUILTINS_HPP

#include <string>
#include <vector>
#include <algorithm>

#include "Builtin.hpp"
#include "CDBuiltin.hpp"
#include "PWDBuiltin.hpp"

/**
 *  A store for builtin commands.
 *
 * This class holds pointers to builtins command objects and execs the commands
 * if they are builtins
 */
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
        /**
         * Execute the builtin command with provided arguments
         *
         * @param cmd is is a string identifier of an *existing* builtin command
         * @param args is a vector of string representing cmd's arguments
         */
        void exec(string cmd, vector<string> args);

        /**
         * Check if a builtin command exist or is implemented
         *
         * @param cmd is a string identifier of a builtin command
         * @return if the builtin command exists or not
         */
        bool has(string cmd);
};

#endif