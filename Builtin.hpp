#include <string>
#include <vector>

using namespace std;

class Builtin {
    private:
        string command;
        vector<string> args;

    public:
        string getCommand();
        vector<string> getArgs();

        virtual void exec() = 0;
};