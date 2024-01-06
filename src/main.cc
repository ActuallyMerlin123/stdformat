/******************************************************************************
 * PROGRAM    STDFORMAT
 * FILE       main.cc
 * AUTHOR     Gleo
 * DATE       05/0/24
 * LANGUAGE   C++20
 *****************************************************************************/

/******************************************************************************
 * DESCRPTION
 * Serves as the 'entry point' file into stdformat,
 * Provides the user interface via Program arguments
 *
 * USAGE
 *
 * PROLOG (Appends a file prolog to a source file)
 * In: `--prolog <filename>`
 * Specifiers:
 *      - `--project`
 *      (Not Implemented)
 *      - `--output/-o <filename>`
 *      - `--<entryname(e.g. --author) <argument(e.g. "Name")`
 *      - `--exclude <entryname>`
 *      - `--read <configfilename>`
 *****************************************************************************/


/********************************ENTRY POINT**********************************/
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <_Config.hh>
#include <Prolog.hh>

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("[ARG] - No viable arguments\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < argc; i++) {
        if (std::strcmp(argv[i], "--version") == 0 ||
                std::strcmp(argv[i], "-v") == 0) {
            std::printf(_STDFORMAT_VERSION);
            std::printf("\nCreated by Gleo\n© 2024 - GPL");
            std::printf("\n");
            return EXIT_SUCCESS;
        } else if (std::strcmp(argv[i], "--help") == 0 ||
                std::strcmp(argv[i], "-h") == 0) {
            const char* helpPage = 
                "Usage: command [OPTIONS] [ARGUMENTS]\n"
                "\n"
                "Description:\n"
                "Adds a dynamic file prolog to a C/C++ source/header file.\n"
                "\n"
                "Options:\n"
                "  -v, --version        Display version in console.\n"
                "  -h, --help           Display 'help' page.\n"
                "  -p, --prolog FILE    Adds prolog to specified file.\n"
                "\n"
                "Created by Gleo\n"
                "stdformat\t© 2024 - GPL\n";
            std::printf("%s", helpPage);
            return EXIT_SUCCESS;
        } else if (std::strcmp(argv[i], "--prolog") == 0 ||
                std::strcmp(argv[i], "-p") == 0) {
            if (argv[i + 1] == NULL) {
                std::perror("[PARSER] - No file provided.");
                return EXIT_FAILURE;
            } 

/***************************** TEMP. DEPRICATED *******************************
 *                                                                            *
 *          if (std::strcmp(argv[i + 2], "--program") == 0) {                 *
 *              if (argv[i + 3] == NULL) {                                    *
 *                  std::perror("[PARSER] - No program name provided");       *
 *              }                                                             *
 *              std::strcpy(user_input, argv[i + 3]);                         *
 *          } else {                                                          *
 *                                                                            *
 *****************************************************************************/

            char user_input[1024];

            std::printf("Enter the program name: ");
            std::scanf("%1023s", user_input);
            form::prolog Prolog(argv[i + 1]);
            Prolog.setProgramName(user_input);
            Prolog.fetchDataset();
            Prolog.writeDataset();
            return EXIT_SUCCESS;
        }
    }
    return EXIT_SUCCESS;
}
