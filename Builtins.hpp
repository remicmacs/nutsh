#ifndef BUILTINS_HPP
#define BUILTINS_HPP

#include <string>
#include <vector>
#include <map>

#include "Builtin.hpp"
#include "CDBuiltin.hpp"
#include "PWDBuiltin.hpp"
#include "EchoBuiltin.hpp"
#include "ExportBuiltin.hpp"
#include "TypeBuiltin.hpp"


using namespace std;
/**
 *  A store for builtin commands.
 *
 * This class holds pointers to builtins command objects and execs the commands
 * if they are builtins
 */
class Builtins {
    private:
        map<string, Builtin *> builtins {
            make_pair ("cd", new CDBuiltin()),
            make_pair ("pwd", new PWDBuiltin()),
            make_pair ("echo", new EchoBuiltin()), 
            make_pair ("export", new ExportBuiltin()),
            make_pair ("type", new TypeBuiltin())
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