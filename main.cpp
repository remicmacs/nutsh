#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>
#include <wordexp.h>

using namespace std;

#include "Builtins.hpp"
#include "Prompt.hpp"
#include "Executor.hpp"

#ifndef MAX_CMDS
#define MAX_CMDS 16
#endif

// Takes user input until they quit the shell, and passes that input as
// arguments to be run.
int main() {
  char ** argv;
  int argc;

  char ** cmdv = static_cast<char **>(malloc(MAX_CMDS * sizeof(char *)));
  int cmdc = 0;
  const char pipe[] = "|";

  wordexp_t p;

  Builtins builtins = Builtins();
  Prompt prompt = Prompt();

  // Keep returning the user to the prompt ad infinitum unless they enter
  // 'quit' or 'exit' (without quotes).
  while (true) {
    // Display a prompt and get a line
    char * input = readline(prompt.getText().c_str());

    // Go to the next iteration if nothing was input
    if (input == NULL || !*input) {
      continue;
    }

    add_history(input);

    // Parsing the pipes
    // Try with  cat Builtin.cpp | grep Builtin
    // The results should be stored in inputs
    // strtok modfies the first input and leave only the first part before the pipe
    // it allows at least the execution of the first part before we implement a real pipe
    char ** cmd = cmdv;

    *cmd = strtok(input, pipe);
    while (*cmd != NULL) {
      cmdc++;
      ++(*cmd) = strtok(NULL, pipe);
    }

    cout << cmdc << " commands given" << endl;

    Executor executor = Executor(input);
    int status = executor.exec();
    prompt.setPreviousReturn(status);

    cmdc = 0;
  }

  free(cmdv);

  return 0;
}