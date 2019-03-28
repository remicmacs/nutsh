#include "Builtins.hpp"

void Builtins::exec(string cmd, vector<string> args) {
    if (cmd == "cd") {
        if (this->cd == NULL) {
            this->cd = new CDBuiltin();
        }
        this->cd->exec(cmd, args);
    } else if (cmd == "pwd") {
        if (this->pwd == NULL) {
            this->pwd = new PWDBuiltin();
        }
        this->pwd->exec(cmd, args);
    } else if (cmd == "echo") {
        if (this->echo == NULL) {
            this->echo = new EchoBuiltin();
        }
        this->echo->exec(cmd, args);
    } else if (cmd == "export") {
        if (this->_export == NULL) {
            this->_export = new ExportBuiltin();
        }
        this->_export->exec(cmd, args);
    } else {
        cout << cmd << " is not implemented yet" << endl;
    }
}

bool Builtins::has(string cmd) {
    return find(builtins.begin(), builtins.end(), cmd) != builtins.end();
}