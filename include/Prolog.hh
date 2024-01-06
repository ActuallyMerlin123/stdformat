/******************************************************************************
 * PROGRAM    STDFORMAT
 * FILE       Prolog.hh
 * AUTHOR     Gleo
 * DATE       05/0/24
 * LANGUAGE   C++20
 *****************************************************************************/

/******************************************************************************
 * DESCRIPTION
 * The 'Prolog'- module provides a class ('prolog'), that fetches data
 * for a struct ('prolog_data'), and writes it to a file, specified in the
 * constructor call of 'prolog'.
 *****************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <climits>
#include <cctype>
#include <unistd.h>
#include <_Config.hh>

namespace form {
    typedef struct prolog_data {
        char* program;
        char* filename;
        char* author;
        char* date;
        char* language;
    } prolog_data;

    class prolog {
        private:
            prolog_data _dataset;
            const char* _filename;
        private:
            char* _fetchProgramName(void);
            char* _fetchFilename(void);
            char* _fetchAuthor(void);
            char* _fetchDate(void);
            char* _fetchLanguages(void);
        private:
            bool _writeToFile(void);
        public:
            explicit prolog(const char* filename);
            explicit prolog(void);
            void setProgramName(const char* name);
            void fetchDataset(void);
            void writeDataset(void);
            ~prolog(void);
    };
}
