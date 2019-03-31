#ifndef EXPORTBUILTIN_HPP
#define EXPORTBUILTIN_HPP

#include "Builtin.hpp"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

/**
 * The `export` shell builtin command
 *
 * Set the value of an environment variable
 */
class ExportBuiltin : public Builtin {
    public:
        ExportBuiltin() : Builtin() {};
        void exec_base();
};

#endif