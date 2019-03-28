#include "Builtin.hpp"

// Include `chdir(2)` system call
#include <unistd.h>

// To convert std::string
#include <cstring>

#include <iostream>
#include <vector>



class EnvBuiltin : public Builtin {
    public:
        EnvBuiltin(string cmd, vector<string> args) : Builtin(cmd, args) {};
        void exec();
    private:
        vector<string> getEnv();
};