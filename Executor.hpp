#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <string>
#include <wordexp.h>
#include <iostream>
#include <vector>
#include <sys/wait.h>

#include "Builtins.hpp"

using namespace std;

class Executor{
  private:
    wordexp_t p;
    char ** argv;
    int argc = 0;

    bool is_valid = false;
    int parse_error = 0;

    // TODO : remove this when the builtins are made static
    Builtins builtins = Builtins();
  public:
    Executor(char * cmd);
    int exec();
};


#endif