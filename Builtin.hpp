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
        Builtin() {};
        string getCommand();
        vector<string> getArgs();

        void exec(string cmd, vector<string> args);
        virtual void exec_base() = 0;
};

#endif