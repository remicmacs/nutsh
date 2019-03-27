#include "Builtin.hpp"

string Builtin::getCommand() {
    return this->command;
}

vector<string> Builtin::getArgs() {
    return this->args;
}

void Builtin::exec(string cmd, vector<string> args) {
    this->command = cmd;
    this->args = args;
    this->exec_base();
}