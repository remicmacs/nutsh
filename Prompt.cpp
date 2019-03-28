#include "Prompt.hpp"

string Prompt::getText() {
    char * tmp;
    string prompt = "";
    string pwd = current_path();
    string user = (tmp = getenv("USER")) == NULL ? "USER" : tmp;

    string previousView = previousReturn == 0 ? "" : "X ";

    char hostArray[HOST_NAME_MAX];
    int hostError = gethostname(hostArray, HOST_NAME_MAX);
    string hostname = hostError != 0 ? "HOST" : string(hostArray);

    prompt = previousView + user + "@" + hostname + " > " + pwd + " > ";
    return prompt;
}

void Prompt::setPreviousReturn(int previous) {
    this->previousReturn = previous;
}