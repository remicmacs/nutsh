#ifndef BUILTIN_HPP
#define BUILTIN_HPP

#include <string>
#include <vector>

using namespace std;

class Builtin {
    private:
        string command;
        vector<string> args;

    public:
        Builtin(string command, vector<string> args) : command(command), args(args) {};
        string getCommand();
        vector<string> getArgs();

        virtual void exec() = 0;
};

#endif