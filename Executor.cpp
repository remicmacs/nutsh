#include "Executor.hpp"

Executor::Executor(char * cmd) {
  this->parse_error = wordexp(cmd, &(this->p), 0);

  switch(this->parse_error) {
    case 0:
      this->argv = p.we_wordv;
      this->argc = p.we_wordc;
      break;
    case WRDE_NOSPACE:
      cout << "wordexp(...): No space left for input allocation" << endl;
      break;
    case WRDE_BADCHAR:
      cout << "wordexp(...): Illegal occurrence of newline or one of |, &, ;, <, >, (, ), {, }." << endl;
      break;
    default:
      cout << "wordexp(...): An unhandled error happened, error code: " << this->parse_error << endl;
      break;
  }
}

int Executor::exec() {
  if (!this->parse_error) {
    return 1;
  }

  int status = 0;

  vector<string> args = vector<string>(argv, argv + argc);
  string prim = args.at(0);

  if (this->builtins.has(prim)) {
    this->builtins.exec(prim, vector<string>(args.begin() + 1, args.end()));
  } else if (prim == "exit") {
    exit(0);
  } else {
    // make a fork
    pid_t pid = fork();

    if (pid == -1 ) {
      cerr << "Fork failed: " << strerror(errno) << endl;
      status = errno;
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
      // TODO: manage background vs foreground
      waitpid(pid, &status, 0);
      status = WEXITSTATUS(status);
    }
  }

  return status;
}