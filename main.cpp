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

  if (argc == 2) {
    char * filename = argv[1];
    freopen(filename, "r", stdin);
  } else if (argc == 3 && string(argv[1]) == "-c"){
    char * input = argv[2];

    wordexp_t p;
    int parse_error = wordexp(input, &p, 0);

    if (parse_error) {
      return 1;
    }

    int status = 0;

    // Test if command is builtin primitive
    vector<string> args = vector<string>(p.we_wordv, p.we_wordv + p.we_wordc);
    string prim = args[0];

    Builtins builtins = Builtins();

    if (builtins.has(prim)) {
      builtins.exec(prim, vector<string>(args.begin() + 1, args.end()));
    } else if (prim == "exit") {
      exit(0);
    } else { // Exec without fork != Executor
      int result = execvp(p.we_wordv[0], p.we_wordv);
      // DEBUG: temporary print
      clog << "Process not replaced for some reason" << endl;
      if (result == -1) {
        cerr << "execvp() system call failed: " << strerror(errno) << endl;
        exit(1);
      }
    }
    exit(status);
  }

  char ** cmdv = new char*[MAX_CMDS];
  int cmdc = 0;
  const char pipe[] = "|";

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
    char ** cmd = cmdv;

    *cmd = strtok(input, pipe);
    while (*cmd != NULL) {
      cmdc++;
      ++(*cmd) = strtok(NULL, pipe);
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
    clog << cmdc << " commands given" << endl;

    Executor executor = Executor(stripped_input, is_bg);
    int status = executor.exec();
    prompt.setPreviousReturn(status);

    cmdc = 0;
  }

  delete cmdv;

  return 0;
}