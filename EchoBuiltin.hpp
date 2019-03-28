#ifndef ECHOBUILTIN_HPP
#define ECHOBUILTIN_HPP

#include "Builtin.hpp"
#include <iostream>

/**
 * The `echo` shell builtin command
 */
class EchoBuiltin : public Builtin {
    private:
        /* data */
    public:
        EchoBuiltin() : Builtin() {};
        void exec_base();
};

#endif