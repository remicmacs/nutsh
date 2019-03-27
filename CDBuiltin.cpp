#include "CDBuiltin.hpp"

void CDBuiltin::exec_base() {
    string target = "";
    vector<string> args = this->getArgs();
    if (!this->getArgs().empty()) target = this->getArgs().at(0);

    chdir(target.c_str());

    // TODO: replace by system climits
    // TODO: return it for modification of the prompt maybe ?
    char * mycwd = new char[100000];
    mycwd = getcwd(mycwd, 10000);

    return;
}