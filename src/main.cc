//
// main for stformat
// by Gleo
//

#include <iostream>
#include "modules/proj.hh"

using namespace std;

int main(int argc, char* argv[]) {

    /* check if there are too much args */
    if (argc != 1) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return EXIT_SUCCESS;
    }

    string filename = argv[1];

    proj::createProject(filename);

    return EXIT_SUCCESS;
}
