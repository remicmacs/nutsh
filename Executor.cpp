#include "Executor.hpp"

pid_t actual_pid;

Executor::Executor(char * cmd, Executor * next, Executor * previous, bool is_bg) {
  this->next = next;
  this->previous = previous;
  this->is_bg = is_bg;
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


void signal_handler(int s){
    cout << endl;
    cout << "Kill pid : " << actual_pid << endl;
    kill(actual_pid,SIGKILL);
    actual_pid = getpid();
}

int Executor::exec() {
  if (this->parse_error) {
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

    //signal handling only if process is not in background
    if (!this->is_bg) {
    actual_pid = pid;
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = signal_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
    }


    if (pid == -1 ) {
      cerr << "Fork failed: " << strerror(errno) << endl;
      status = errno;
    } else if (pid == 0) { // inside the child
    
      /*if (this->next != nullptr && this->previous != nullptr) {
        cout << "Coming through !" << endl;
        pipe(fds);

        // If there is no next, we can close the output
        if (this->next != nullptr) {
          dup2(this->fds[0], 0);
        } else {
          close(this->fds[1]);
        }

        // If there is no previous, we can close the input
        if (this->previous != nullptr) {
          dup2(this->fds[1], 1);
        } else {
          close(this->fds[0]);
        }
      }*/

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
      if (!this->is_bg) {
        waitpid(pid, &status, 0);
        status = WEXITSTATUS(status);
        actual_pid = getpid(); // When proccess is done reset the pid
      } // else not waiting on it
    }
  }

  return status;
}

void Executor::set_next(Executor * next) {
  this->next = next;
}

void Executor::set_previous(Executor * previous) {
  this->previous = previous;
}
