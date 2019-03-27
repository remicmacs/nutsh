#include "CDBuiltin.hpp"

void CDBuiltin::exec() {
    cerr << "Begin overriden exec" << endl;

    string target = this->getArgs().at(0);

    cerr << "Got arg" << endl;
    chdir(target.c_str());

    cerr << "Changed dir" << endl;

    char * mycwd = new char[100000];

    mycwd = getcwd(mycwd, 10000);

    string landing = string(mycwd);
    cerr << "Landing : " << landing << endl;
    return;
}