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

    // TODO: from there, maybe implement the rest of the parsing of the commands
    // through a dedicated Executor object or so, that will allow us to make pipes
    // and redirects

    // TODO: maybe pass the WRDE_REUSE flag after the first iteration
    int error = wordexp(input, &p, 0);
    if (error != 0) {
      // Parse here wordexp error to find issue
      switch(error) {
        case WRDE_NOSPACE:
          cout << "wordexp(...): No space left for input allocation" << endl;
          break;
        case WRDE_BADCHAR:
          cout << "wordexp(...): Illegal occurrence of newline or one of |, &, ;, <, >, (, ), {, }." << endl;
          break;
        default:
          cout << "wordexp(...): An unhandled error happened, error code: " << error << endl;
          break;
      }
      continue;
    }

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

    // TODO: maybe remove this block, argv is a pointer to the wordexp_t
    // structure which is managed by wordexp.
    // Reset the argv array for next time.
    for (int i=0; i<argc; i++) {
      argv[i] = NULL;
    }

    cmdc = 0;
  }

  free(cmdv);

  return 0;
}