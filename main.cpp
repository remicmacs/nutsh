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
int main(int argc, char ** argv) {

  if (argc > 1) {
    char * filename = argv[1];
    freopen(filename, "r", stdin);
  }

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
      break;
    } else if (!*input) {
      continue;
    }

    add_history(input);

    // Parsing the pipes
    // Try with  cat Builtin.cpp | grep Builtin
    // The results should be stored in inputs
    // strtok modfies the first input and leave only the first part before the pipe
    // it allows at least the execution of the first part before we implement a real pipe
    char ** cmds = cmdv;

    *cmds = strtok(input, pipe);
    while (*cmds != NULL) {
      cmdc++;
      ++(*cmds) = strtok(NULL, pipe);
    }

    // Testing if bg job required
    bool is_bg = input[strlen(input) -1] == '&';

    // Strip input from '&' char if needed
    char * stripped_input;
    if (is_bg) {
      stripped_input = new char[strlen(input) - 1];
      strncpy(stripped_input, input, strlen(input) - 2);
      stripped_input[strlen(input) - 2] = '\0';
      delete input;
    } else {
      stripped_input = input;
    }

    // DEBUG: remove after use
    cout << cmdc << " commands given" << endl;
    cout << cmdv[0] << endl;
    cout.flush();

    /*vector<Executor *> executors = vector<Executor *>();

    for (int index = 0; index < cmdc; index++) {
      char * cmd = *(cmdv + index);
      cout << cmd << endl;
      executors.push_back(new Executor(cmd));
    }

    for (unsigned int index = 0; index < executors.size(); index++) {
      if (index > 0) {
        executors[index]->set_previous(executors[index - 1]);
      }

      if (index < executors.size() - 1) {
        executors[index]->set_next(executors[index + 1]);
      }

      cout << executors.size() << endl;
    }*/

    Executor executor = Executor(stripped_input, is_bg);
    int status = executor.exec();
    prompt.setPreviousReturn(status);

    cmdc = 0;
  }

  delete cmdv;

  return 0;
}