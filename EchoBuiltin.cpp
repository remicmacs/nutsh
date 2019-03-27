#include "EchoBuiltin.hpp"

void EchoBuiltin::exec() {
    for (string arg:getArgs()) {
        cout << arg << ' ';
    }
    cout << endl;
}