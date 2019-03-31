#ifndef BUILTIN_HPP
#define BUILTIN_HPP

#include <string>
#include <vector>

using namespace std;

/**
 * Abstract base class for builtin commands of the shell
 *
 * This abstract class requires `exec_base` to be implemented in derived classes
 */
class Builtin {
    private:
        string command;
        vector<string> args;

    public:
        /**
         * Explicit default constructor
         */
        Builtin() {};

        /**
         * Getter for `args` property
         *
         * Return the list of arguments of the builin command
         */
        vector<string> get_args();

        /**
         * Load command name and arguments and execute builtin command
         *
         * Requires an implementation for `exex_base` function
         *
         * @see Builtin::exec
         * @param cmd is the builtin command identifier
         * @param args is the eventual list of arguments of the builtin command
         */
        void exec(string cmd, vector<string> args = vector<string>());

        /**
         * Specific implementation of a builtin command.
         *
         * When this command is executed, properties are required to be
         * initialized.
         */
        virtual void exec_base() = 0;
};

#endif