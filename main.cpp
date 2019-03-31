#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>

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
  char ** cmdv = new char*[MAX_CMDS];
  int cmdc = 0;
  const char pipe[] = "|";

  Builtins builtins = Builtins();
  Prompt prompt = Prompt();

  // Keep returning the user to the prompt ad infinitum unless they enter
  // 'quit' or 'exit' (without quotes).
  while (true) {
    // Display a prompt and get a line
    char * input = readline(prompt.getText().c_str());

    // Go to the next iteration if nothing was input
    if (input == NULL) {
      continue;
    } else if (!*input) {
      break;
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

    // DEBUG: remove after use
    clog << cmdc << " commands given" << endl;

    Executor executor = Executor(input);
    int status = executor.exec();
    prompt.setPreviousReturn(status);

    cmdc = 0;
  }

  delete cmdv;

  return 0;
}