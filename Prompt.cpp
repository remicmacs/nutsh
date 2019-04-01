#include "Prompt.hpp"

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 64
#endif

// Set the colours with ANSI Escape Codes :
// https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
// Just change 'ESC' with '\033'

string Prompt::getText() {
    char * tmp;

    // Build the path string
    string pwd = current_path();
    string home = getenv("HOME");
    if (pwd.find(home, 0) == 0) {
        pwd.replace(0, home.length(), "~");
    }

    // Build the user string
    // \033[48;5;124m\033[38;5;232m is red background and black foreground
    // \033[38;5;196m is red foreground
    // \033[0;1m resets (0) and set the prompt to bold (1)
    string user = (tmp = getenv("USER")) == NULL ? "USER" : tmp;
    string userColor = user == "root" ? "\033[48;5;124m\033[38;5;232m " : "\033[38;5;196m";
    user = user == "root" ? user + " \033[0;1m" : user;

    // Add an indicator in case of an error in the previous process
    // \033[38;5;160m dark red foreground
    string previousView = previousReturn == 0 ? "" : "\033[38;5;160mX ";

    // Build the hostname
    char hostArray[HOST_NAME_MAX];
    int hostError = gethostname(hostArray, HOST_NAME_MAX);
    string hostname = hostError != 0 ? "HOST" : string(hostArray);

    // Build the prompt
    // Comma-first notation
    string prompt = "\033[1m" + previousView
        + userColor + user 
        + "\033[37m" + " at " 
        + "\033[38;5;214m" + hostname 
        + "\033[37m" + " in " 
        + "\033[38;5;76m" + pwd
        + "\033[37m" + " > "
        + "\033[0m"
        ;
    
    return prompt;
}

void Prompt::setPreviousReturn(int previous) {
    this->previousReturn = previous;
}