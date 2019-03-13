#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

#include "utils.h"

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

    // Reset the argv array for next time.
    for (int i=0; i<argc; i++)
      argv[i] = NULL;
  }

  return 0;
}