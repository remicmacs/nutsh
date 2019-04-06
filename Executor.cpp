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

    // If there is a previous executor, we create a pipe
    // to connect the previous one to this one
    if (this->has_previous()) {
      pipe(this->fds);
    }

    // If there is a next executor, we'll get its end of the pipe
    if (this->has_next()) {
      this->next_fds_out = this->next->get_stdout();
    }

    // Make a fork
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

      // For piped commands, we'll set the input and output streams
      if (this->is_piped()) {

        // We don't use the output end of the pipe in this process
        // we'll use the end of the pipe of the next process if needed
        if (!this->is_start()) {
          close(this->fds[1]);
        }

        // Connect the output of the command to the output of the pipe
        // of the next process
        if (this->has_next()) {
          dup2(this->next_fds_out, 1);
        }

        // Connect the input of the command to the input of the pipe
        if (this->has_previous()) {
          dup2(this->fds[0], 0);
        }
      }

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

      // Launch the previous command while this one is running
      if (this->has_previous()) {
        status = this->previous->exec();
      }

      // Guarantees that the previous process stops sending data
      // and sends EOF
      if (!this->is_start()) {
        close(this->fds[1]);
      }

      if (!this->is_bg) { // TODO: manage background vs foreground
        waitpid(pid, &status, 0);
        status = WEXITSTATUS(status);
        actual_pid = getpid(); // When process is done reset the pid
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

int Executor::get_stdin() {
  return this->fds[0];
}

int Executor::get_stdout() {
  return this->fds[1];
}

void Executor::set_stdin(int stdin) {
  this->fds[0] = stdin;
}

void Executor::set_stdout(int stdout) {
  this->fds[1] = stdout;
}

void Executor::set_next_stdout(int stdout) {
  this->next_fds_out = stdout;
}

bool Executor::is_start() {
  return this->previous == nullptr;
}

bool Executor::is_end() {
  return this->next == nullptr;
}

bool Executor::is_piped() {
  return (this->next != nullptr || this->previous != nullptr);
}

bool Executor::has_next() {
  return this->next != nullptr;
}

bool Executor::has_previous() {
  return this->previous != nullptr;
}