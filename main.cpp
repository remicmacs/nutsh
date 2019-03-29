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

#include "utils.h"

#include "Builtins.hpp"
#include "Prompt.hpp"

// Takes user input until they quit the shell, and passes that input as
// arguments to be run.
int main() {
  char ** argv;
  int argc;
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
    wordexp(input, &p, 0);
    argv = p.we_wordv;
    argc = p.we_wordc;

    vector<string> args = vector<string>(argv, argv + argc);
    string prim = args.at(0);

    if (builtins.has(prim)) {
        builtins.exec(prim, vector<string>(argv + 1, argv + argc));
    } else if (prim == "exit") {
      exit(0);
    } else {
      // make a fork
      pid_t pid = fork();

      if (pid == -1 ) {
        cerr << "Fork failed: " << strerror(errno) << endl;
      } else if (pid == 0) { // inside the child
        int result = execvp(argv[0], argv);

        // Executed only if execvp failed (mostly )
        // FIXME: reached this after a `hexdump nutsh` but the filename `nutsh`
        // had been written after inserting a tab by mistake and deleting it // // with backspace.
        // `execvp() system call failed: No such file or directory`
        // Is it reproducible ?
        // DEBUG: temporary print
        clog << "Process not replaced for some reason" << endl;
        if (result == -1) {
          cerr << "execvp() system call failed: " << strerror(errno) << endl;
          exit(1);
        }
      } else { // parent of fork
        int status;

        // TODO: manage background vs foreground
        waitpid(pid, &status, 0);

        // Give the status code to the shell
        prompt.setPreviousReturn(WEXITSTATUS(status));
      }
    }

    // Reset the argv array for next time.
    for (int i=0; i<argc; i++) {
      argv[i] = NULL;
    }
  }

  return 0;
}