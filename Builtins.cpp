#include "Builtins.hpp"

void Builtins::exec(string cmd, vector<string> args) {

    // All commands reaching here should be checked as valid keys
    if (this->has(cmd)) {
        this->builtins[cmd]->exec(cmd, args);
    } else {
        cout << cmd << " is not implemented yet" << endl;
    }
}

bool Builtins::has(string cmd) {
    return (!(this->builtins.find(cmd) == this->builtins.end()));
}