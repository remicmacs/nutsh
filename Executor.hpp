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

    int fds[2];
    int next_fds_out;
    int next_fds_in;

    Executor * next;
    Executor * previous;

    bool is_end();
    bool is_start();
    bool is_piped();
    bool has_next();
    bool has_previous();

    // TODO : remove this when the builtins are made static
    Builtins builtins = Builtins();
  public:
    Executor(char * cmd) : Executor(cmd, nullptr, nullptr, false) {};
    Executor(char * cmd, bool is_bg) : Executor(cmd, nullptr, nullptr, is_bg) {};
    Executor(char * cmd, Executor * next, Executor * previous, bool is_bg);

    int exec();

    int get_stdin();
    int get_stdout();
    void set_stdin(int stdin);
    void set_stdout(int stdout);
    void set_next_stdout(int stdout);
    void set_next_stdin(int stdin);

    void set_next(Executor * next);
    void set_previous(Executor * previous);
};

  void signal_handler(int s);


#endif