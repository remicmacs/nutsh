#include "CDBuiltin.hpp"

void CDBuiltin::exec_base() {
    string target = this->getArgs().at(0);
    chdir(target.c_str());

    char * mycwd = new char[100000];

    mycwd = getcwd(mycwd, 10000);

    string landing = string(mycwd);
    cerr << "Landing : " << landing << endl;
    return;
}