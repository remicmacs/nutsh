#ifndef PROMPT_HPP
#define PROMPT_HPP

#include <string>
#include <climits>
#include <unistd.h>
#include <filesystem>
#include <pwd.h>

using namespace std;
using namespace filesystem;

class Prompt {
    private:
        int previousReturn = 0;
    public:
        string getText();
        void setPreviousReturn(int previous);
};

#endif