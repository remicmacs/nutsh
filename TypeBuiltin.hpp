#ifndef TYPEBUILTIN_HPP
#define TYPEBUILTIN_HPP

#include "Builtin.hpp"


#include <sys/types.h> 
#include <sys/stat.h> 
#include <time.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/sysmacros.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <climits>
#include <sstream>
#include<iterator>
#include <algorithm>


/**
 * The `type` shell builtin command
 */
class TypeBuiltin : public Builtin {
    public:
        TypeBuiltin() : Builtin() {};
        void exec_base();
        
};

template<char delimiter>
class WordDelimitedBy : public std::string
{};

#endif