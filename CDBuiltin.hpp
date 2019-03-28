#ifndef CDBUILTIN_HPP
#define CDBUILTIN_HPP

#include "Builtin.hpp"

// TODO: Use built in constants in climits for max buffer size, etc.

// Include `chdir(2)` system call
#include <unistd.h>

// To convert std::string
#include <cstring>

#include <iostream>

#include <climits>

/**
 * The `cd` shell builtin command
 */
class CDBuiltin : public Builtin {
    public:
        CDBuiltin() : Builtin() {};
        void exec_base();
};

#endif