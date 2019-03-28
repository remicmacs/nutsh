#include "EnvBuiltin.hpp"

void EnvBuiltin::exec() {

    /* TMP PARSER */
 /*    string env_var = this->getArgs().at(0);
    chdir(env_var.c_str());

    char * mycwd = new char[100000];

    mycwd = getcwd(mycwd, 10000);

    string landing = string(mycwd);
    cerr << "Landing : " << landing << endl;  */

    vector<string> test = getEnv();
    vector<string>::iterator it;  //Un itérateur sur une deque d'entiers

    //Et on itère sur la deque
    for(it = test.begin(); it!=test.end(); ++it)
    {
        cout << *it << endl;    //On accède à l'élément pointé via l'étoile
    }
    return;
}


vector<string> EnvBuiltin::getEnv(){
    extern char **environ;
    int count = 0;
    vector<string> env;
     while(environ[count] != NULL)
   {
         env.push_back(environ[count]);
         count++;
   }
   return env;

}