#include "Builtin.hpp"

string Builtin::getCommand() {
    return this->command;
}

vector<string> Builtin::getArgs() {
    return this->args;
}