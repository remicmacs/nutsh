#include "PWDBuiltin.hpp"

void PWDBuiltin::exec_base() {
    char * cwd = new char[PATH_MAX];

    cwd = getcwd(cwd, PATH_MAX);

    string cwdStr = string(cwd);
    cout << cwdStr << endl;
    return;
}