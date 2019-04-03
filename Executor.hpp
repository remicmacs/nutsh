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

    int fds[2];

    Executor * next;
    Executor * previous;

    // TODO : remove this when the builtins are made static
    Builtins builtins = Builtins();
  public:
    Executor(char * cmd) : Executor(cmd, nullptr, nullptr) {};
    Executor(char * cmd, Executor * next, Executor * previous);
    int exec();

    int get_stdin();
    int get_stdout();
};


#endif