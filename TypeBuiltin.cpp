#include "TypeBuiltin.hpp"

void TypeBuiltin::exec_base() {
    string target = "";
    struct stat sb;
    vector<string> args = this->get_args();
    if (!args.empty()) target = args.at(0);
    if(target.empty()) return;

    lstat(target.c_str(), &sb);

         string path =  getenv("PATH");
        string s = ".:" + path;
        string delimiter = ":";

        size_t pos = 0;
        string token;
        string folder;
        string result;

        while ((pos = s.find(delimiter)) != string::npos) {
            token = s.substr(0, pos);
            
             folder = token +  "/" + target.c_str();
            s.erase(0, pos + delimiter.length());
            if ((sb.st_mode & S_IFMT)!=S_IFDIR && token != "/usr/bin") {
                 if( access(folder.c_str(), X_OK ) == 0 ) {
                    result = target + " is " + folder;
                    cout << result << endl;
                    return;  
                }
            }
            }
    
      vector<string> builtins = {"cd","type","echo","pwd","export"};
        if (find(builtins.begin(), builtins.end(), target) != builtins.end())
        {
            cout << target << " is shell primitive" <<endl;
            return;
        }

    
    cout << "File type:                " ;

    switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:  cout << "block device" << endl;            break;
    case S_IFCHR:  cout << "character device" << endl;        break;
    case S_IFDIR:  cout << "directory" << endl;               break;
    case S_IFIFO:  cout <<"FIFO/pipe" << endl;               break;
    case S_IFLNK:  cout <<"symlink" << endl;                 break;
    case S_IFREG:  cout << "regular file" << endl;            break;
    case S_IFSOCK: cout << "socket" << endl;                  break;
    default: cout << "unknown" << endl ;                      break;
    }

    cout << "I-node number:            " << static_cast<long> (sb.st_ino) << endl;
    cout << "Mode:                     " << static_cast< unsigned long>  (sb.st_mode) <<  " (octal)" << endl;
    cout << "Link count:               " << static_cast<long> (sb.st_nlink) << endl;
    cout << "Ownership:                UID=" <<  static_cast<long> (sb.st_uid) << ", GID=" <<  static_cast<long> (sb.st_gid) << endl;
    cout << "File size:                " <<  static_cast<long long> (sb.st_size) << " bytes" << endl;

    
    return;
}