#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

#include "utils.h"

#include "Builtins.hpp"

#define MAX_ARGS 64

// Takes user input until they quit the shell, and passes that input as
// arguments to be run.
int main() {
  char *argv[MAX_ARGS];
  int argc;

  Builtins builtins = Builtins();

  // Keep returning the user to the prompt ad infinitum unless they enter
  // 'quit' or 'exit' (without quotes).
  while (true) {
    // Display a prompt.
    cout << "Nutsh ({}) > ";

    // Read in a command from the user.
    argc = read_args(argv);

    // Implement here the parsing/execution logic

    // Conversion to C++ string for easier comparison
    string prim = string(argv[0]);

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

        // TODO: save as global state of shell for prompt ?
        cout << WEXITSTATUS(status);
      }
    }

    // Reset the argv array for next time.
    for (int i=0; i<argc; i++) {
      argv[i] = NULL;
    }
  }

  return 0;
}