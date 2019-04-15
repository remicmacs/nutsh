#include "Prompt.hpp"
#include "Executor.hpp"

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 64
#endif

// Set the colours with ANSI Escape Codes :
// https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
// Just change 'ESC' with '\033'

string Prompt::white = Prompt::escape("\033[37m");
string Prompt::orange = Prompt::escape("\033[38;5;214m");
string Prompt::green = Prompt::escape("\033[38;5;76m");
string Prompt::red = Prompt::escape("\033[38;5;196m");
string Prompt::reverse_red = Prompt::escape("\033[48;5;124m\033[38;5;232m");
string Prompt::dark_red = Prompt::escape("\033[38;5;160m");
string Prompt::reset = Prompt::escape("\033[0m");
string Prompt::bold = Prompt::escape("\033[1m");

string Prompt::escape(string to_decorate) {
    return PROMP_START_IGNORE + to_decorate + PROMPT_END_IGNORE;
}

string Prompt::getText() {
    char * tmp;

    // Build the path string
    char * cwd = new char[PATH_MAX];
    cwd = getcwd(cwd, PATH_MAX);
    string pwd = string(cwd);

    // Get HOME environment
    string home = getenv("HOME");
    if (pwd.find(home, 0) == 0) {
        pwd.replace(0, home.length(), "~");
    }

    // Shorten the long folder names in path
    string fragment;
    istringstream tokenStream(pwd);
    string new_pwd = "";
    while (getline(tokenStream, fragment, '/')) {
        if (fragment.length() > 6) {
            fragment = fragment.substr(0, 3) + "...";
        }
        new_pwd += fragment + "/";
    }

    pwd = new_pwd.substr(0, new_pwd.length() - 1);

    // Build the user string
    string user(getpwuid(geteuid())->pw_name);
    string userColor = user == "root" ? Prompt::reverse_red + " " : Prompt::red;
    user = user == "root" ? user + " " + Prompt::reset + Prompt::bold : user;

    // Add an indicator in case of an error in the previous process
    string previousView = previousReturn == 0 ? "" : Prompt::dark_red + "X ";

    // Build the hostname
    char hostArray[HOST_NAME_MAX];
    int hostError = gethostname(hostArray, HOST_NAME_MAX);
    string hostname = hostError != 0 ? "HOST" : string(hostArray);

    // TODO: Get the git status
    // Idea : use fmemopen to create a file pointer to a string
    // so we can use the future feature of pipe/redirect of the executor
    // to dump the output of git status -s into a string (actually a char *)

    // Build the prompt
    // Comma-first notation
    string prompt = Prompt::bold + previousView
        + userColor + user 
        + Prompt::white + " at " 
        + Prompt::orange + hostname 
        + Prompt::white + " in " 
        + Prompt::green + pwd
        + Prompt::white + " > "
        + Prompt::reset
        ;
    
    return prompt;
}

void Prompt::setPreviousReturn(int previous) {
    this->previousReturn = previous;
}