#ifndef PWDBUILTIN_HPP
#define PWDBUILTIN_HPP

#include "Builtin.hpp"
#include <unistd.h>
#include <iostream>
#include <limits.h>

class PWDBuiltin : public Builtin {
    public:
        PWDBuiltin() : Builtin() {};
        PWDBuiltin(string cmd, vector<string> args = vector<string>()) : Builtin(cmd, args) {};
        void exec_base();
};

#endif