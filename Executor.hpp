#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <string>
#include <wordexp.h>
#include <iostream>
#include <vector>
#include <signal.h>

#include <sys/wait.h>

#include "Builtins.hpp"

using namespace std;

class Executor{
  private:
    wordexp_t p;
    char ** argv;
    int argc = 0;

    bool is_valid = false;
    bool is_bg;
    int parse_error = 0;

    // TODO : remove this when the builtins are made static
    Builtins builtins = Builtins();
  public:
    Executor(char * cmd) : Executor(cmd, false) {};
    Executor(char * cmd, bool is_bg);
    int exec();

};

  void signal_handler(int s);


#endif