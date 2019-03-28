#include "CDBuiltin.hpp"

void CDBuiltin::exec_base() {
    string target = "";

    vector<string> args = this->get_args();
    if (!args.empty()) target = args.at(0);

    chdir(target.c_str());

    char * mycwd = new char[PATH_MAX];
    mycwd = getcwd(mycwd, PATH_MAX);

    return;
}