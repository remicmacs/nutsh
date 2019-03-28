#include "EchoBuiltin.hpp"

void EchoBuiltin::exec_base() {
    for (string arg:get_args()) {
        cout << arg << ' ';
    }
    cout << endl;
}