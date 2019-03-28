#ifndef PWDBUILTIN_HPP
#define PWDBUILTIN_HPP

#include "Builtin.hpp"
#include <unistd.h>
#include <iostream>
#include <limits.h>

/**
 * The `pwd` shell builtin command
 */
class PWDBuiltin : public Builtin {
    public:
        PWDBuiltin() : Builtin() {};
        void exec_base();
};

#endif