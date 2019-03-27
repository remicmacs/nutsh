#include "EchoBuiltin.hpp"

void EchoBuiltin::exec_base() {
    for (string arg:getArgs()) {
        cout << arg << ' ';
    }
    cout << endl;
}