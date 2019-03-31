#include "ExportBuiltin.hpp"

void ExportBuiltin::exec_base() {
    vector<string> args = this->get_args();
    bool noargs = args.empty();

    if (noargs || this->get_args().at(0) == "-p") {

        // Setting output prefix according version of the command
        string prefix = "";
        if (!noargs) prefix = "export ";

        extern char ** environ;
        // Looping on environment variables
        char * curr_env_var;
        for (int i = 0; (curr_env_var = environ[i]) != NULL ; i++) {
            string env_var_str = string(curr_env_var);
            cout << prefix << env_var_str << endl;
        }
    } else { // Export Key=value pair
        string key;
        string value;
        string delimiter = "=";

        string key_value_pair = this->get_args()[0];

        string::size_type pos = key_value_pair.find(delimiter);

        // No delimiter found in key / value pair
        if (pos == string::npos) return;

        key = key_value_pair.substr(0, pos);
        value = key_value_pair.substr(pos+1, string::npos);

        // Overwrite existing value
        setenv(key.c_str(), value.c_str(), 1);
    }
    return;
}