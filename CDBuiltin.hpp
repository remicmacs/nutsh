#include "Builtin.hpp"

// Include `chdir(2)` system call
#include <unistd.h>

// To convert std::string
#include <cstring>

#include <iostream>


class CDBuiltin : public Builtin {
    public:
        CDBuiltin(string cmd, vector<string> args) : Builtin(cmd, args) {};
        void exec();
};