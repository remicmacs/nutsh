#include "ExportBuiltin.hpp"

void ExportBuiltin::exec_base() {
    // TODO: Maybe factor code in a class to execute external commands?
    // Export alone == `env`
    // It's weird to do that
    // TODO: `export -p` syntax == same as `env` but with `export` prefix on
    // each key/value pair. Maybe do it properly without call to exec ?
    if (this->get_args().empty()) {
        // make a fork
        pid_t pid = fork();

        if (pid == -1 ) {
            cerr << "Fork failed: " << strerror(errno) << endl;
        } else if (pid == 0) { // inside the child
            string env_cmd = "env";
            char ** args = new char * [1];
            char * env_cmd_c = new char[env_cmd.size()+1];
            strcpy(env_cmd_c, env_cmd.c_str());
            args[0] = env_cmd_c;

            int result = execvp(env_cmd_c, args);

            // Executed only if execvp failed (mostly )
            // DEBUG: temporary print
            clog << "Process not replaced for some reason" << endl;
            if (result == -1) {
            cerr << "execvp() system call failed: " << strerror(errno) << endl;
            exit(1);
            }
        } else { // parent of fork
            int status;

            waitpid(pid, &status, 0);

            cout << WEXITSTATUS(status);
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