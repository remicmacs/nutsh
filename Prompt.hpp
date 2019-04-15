#ifndef PROMPT_HPP
#define PROMPT_HPP

#include <string>
#include <climits>
#include <unistd.h>
#include <pwd.h>

#define PROMP_START_IGNORE "\001"
#define PROMPT_END_IGNORE "\002"

using namespace std;

class Prompt {
    private:
        int previousReturn = 0;
    public:
        string getText();
        void setPreviousReturn(int previous);

        static string white;
        static string orange;
        static string green;
        static string red;
        static string reverse_red;
        static string dark_red;
        static string reset;
        static string bold;
        static string escape(string to_decorate);
};

#endif