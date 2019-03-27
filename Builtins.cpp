#include "Builtins.hpp"

void Builtins::exec(string cmd, vector<string> args) {
    if (cmd == "cd") {
        if (cd == NULL) {
            cd = new CDBuiltin();
        }
        cd->exec(cmd, args);
    } else if (cmd == "pwd") {
        if (pwd == NULL) {
            pwd = new PWDBuiltin();
        }
        pwd->exec(cmd, args);
    } else if (cmd == "echo") {
        if (echo == NULL) {
            echo = new EchoBuiltin();
        }
        echo->exec(cmd, args);
    } else {
        cout << cmd << " is not implemented yet" << endl;
    }
}

bool Builtins::has(string cmd) {
    return find(builtins.begin(), builtins.end(), cmd) != builtins.end();
}