#ifndef ECHOBUILTIN_HPP
#define ECHOBUILTIN_HPP

#include "Builtin.hpp"
#include <iostream>

class EchoBuiltin : public Builtin {
    private:
        /* data */
    public:
        EchoBuiltin() : Builtin() {};
        EchoBuiltin(string cmd, vector<string> args) : Builtin(cmd, args) {};
        void exec_base();
};

#endif