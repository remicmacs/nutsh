#include "Builtin.hpp"

void Builtin::exec(string cmd, vector<string> args) {
    this->command = cmd;
    this->args = args;
    this->exec_base();
}

vector<string> Builtin::get_args() {
    return this->args;
}