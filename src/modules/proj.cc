//
// library for project templating
// stdformat by Gleo
//

#include "proj.hh"
#include <iostream>
#include <unistd.h>
#include <filesystem>

using namespace std;

int proj::createProject(string filename) {
    filesystem::path cwd = filesystem::current_path();
    const string PROJECTPATH = cwd.string() + filename;

    cout << PROJECTPATH << endl;

    return 0;
}
