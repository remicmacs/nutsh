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

#include "CDBuiltin.hpp"
#include "PWDBuiltin.hpp"

#define MAX_ARGS 64

// Takes user input until they quit the shell, and passes that input as
// arguments to be run.
int main() {
  char *argv[MAX_ARGS], *cmd1[MAX_ARGS], *cmd2[MAX_ARGS];
  int argc;

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

    // Test builtins
    // TODO: change to hash map string -> Builtin object
    // Or factory pattern ?
    if (prim == "cd") { // If it is the cd builtin
      // pass only first argument (cannot cd in multiple directories)
      vector<string> myArg;
      myArg.push_back(string(argv[1]));

      // Build cd builtin command object
      CDBuiltin myCd = CDBuiltin(string(argv[0]), myArg);
      myCd.exec();
    } else if (prim == "pwd") {
      PWDBuiltin pwd = PWDBuiltin(string(argv[0]));
      pwd.exec();
    } else if (prim == "exit") {
      exit(0);
    }

    // Reset the argv array for next time.
    for (int i=0; i<argc; i++) {
      argv[i] = NULL;
    }
  }

  return 0;
}