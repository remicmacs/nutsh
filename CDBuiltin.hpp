#ifndef CDBUILTIN_HPP
#define CDBUILTIN_HPP
// TODO: Use built in constants in climits for max buffer size, etc.
#include "Builtin.hpp"

// Include `chdir(2)` system call
#include <unistd.h>

// To convert std::string
#include <cstring>

#include <iostream>


class CDBuiltin : public Builtin {
    public:
        CDBuiltin() : Builtin() {};
        void exec_base();
};

#endif