#ifndef TYPEBUILTIN_HPP
#define TYPEBUILTIN_HPP

#include "Builtin.hpp"


#include <sys/stat.h> 
#include <stdio.h> 
#include <stdlib.h> 
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
        bool is_builtin(string target);
        bool is_executable(struct stat sb, string target);
        void target_infos(struct stat sb);
       
};



#endif