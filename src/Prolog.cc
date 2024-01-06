#include <Prolog.hh>

/************************************PUBLIC************************************/

form::prolog::prolog(const char* filename) : _filename(filename)
{
    _dataset.program = (char*)malloc(100 * sizeof(char));
    _dataset.filename = (char*)malloc(100 * sizeof(char));
    _dataset.author = (char*)malloc(100 * sizeof(char));
    _dataset.date = (char*)malloc(20 * sizeof(char));
    _dataset.language = (char*)malloc(50 * sizeof(char));
}

void form::prolog::setProgramName(const char* name)
{
    char nameUpper[std::strlen(name)];
    for (int i = 0; i < std::strlen(name); i++) {
        nameUpper[i] = std::toupper(name[i]);
    }
    std::strcpy(this->_dataset.program, nameUpper);
}

void form::prolog::fetchDataset(void)
{
    if (this->_dataset.program == NULL) {
        std::perror("[PROLOG] - The 'program' trait is empty.");
    }
    // this->_dataset.filename = this->_fetchFilename();
    // this->_dataset.author = this->_fetchAuthor();
    // this->_dataset.date = this->_fetchDate();
    // this->_dataset.language = this->_fetchLanguages();
    std::strcpy(this->_dataset.filename, this->_fetchFilename());
    std::strcpy(this->_dataset.author, this->_fetchAuthor());
    std::strcpy(this->_dataset.date, this->_fetchDate());
    std::strcpy(this->_dataset.language, this->_fetchLanguages());
}

form::prolog::~prolog(void)
{
    free(_dataset.program);
    free(_dataset.filename);
    free(_dataset.author);
    free(_dataset.date);
    free(_dataset.language);
}

void form::prolog::writeDataset(void)
{
    this->_writeToFile();
}

/************************************PRIVAT************************************/

char* form::prolog::_fetchFilename(void)
{
    const char* dot_pos = strchr(this->_filename, '.');

    if (dot_pos == NULL) {
        std::perror("[PROLOG] - Filename could not be determinated.");
        char rval[] = "";
        char* rvalstr = rval;
        return rvalstr;
    }

    int substring_length = dot_pos - this->_filename;

    char substring[substring_length + 1];
    strncpy(substring, this->_filename, substring_length);
    substring[substring_length] = '\0';

    char* filename = substring;
    
    std::printf("Fetched filename: %s\n", filename);

    return filename;
}

char* form::prolog::_fetchAuthor(void)
{
    char* login = getlogin();
    std::printf("Fetched author as: %s\n", login);

    return login;
}

char* form::prolog::_fetchDate(void)
{
    time_t currentTime;
    struct tm *localTime;
    char dateString[20];

    currentTime = time(NULL);
    localTime = localtime(&currentTime);
    strftime(dateString, sizeof(dateString), "%d/%m/%y", localTime);

    char* dateCStr = dateString;
    
    std::printf("Fetched date as: %s\n", dateCStr);

    return dateCStr;
}

char* form::prolog::_fetchLanguages(void)
{
    const char *dot = strrchr(this->_filename, '.');
    if (dot == NULL) {
        std::perror("[PROLOG] - Filename could not be determined.\n");
        char* error;
        std::strcpy(error, "Unknown Filetype");
        return error;
    }

    const char *substring = dot + 1;
    char extension[10];
    strcpy(extension, substring);

    char language[20];

    if (strcmp(extension, "c") == 0) {
        strcpy(language, "C");
    } else if (strcmp(extension, "cxx") == 0 ||
            strcmp(extension, "cpp") == 0 ||
            strcmp(extension, "cc") == 0 ||
            strcmp(extension, "C") == 0) {
        strcpy(language, "C++");
    } else if (strcmp(extension, "h") == 0 ||
            strcmp(extension, "hh") == 0) {
        strcpy(language, "Header File");
    } else {
        std::perror("[PROLOG] - Filetype could not be determined.\n");
        strcpy(language, "Unknown Filetype");
    }

    std::printf("Fetched extension as: %s\n", language);

    char* filetype = language;

    return filetype; 
}

bool form::prolog::_writeToFile(void)
{
    std::FILE* file;
    char filenamepath[PATH_MAX];

    if (realpath(this->_filename, filenamepath) == nullptr) {
        std::perror("[PATH] Could not resolve the path.");
        return false;
    }

    file = std::fopen(filenamepath, "r+");

    if (file == nullptr) {
        std::perror("[PROLOG] - Could not open file.");
        return false;
    }

    std::fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);

    std::rewind(file);

    char *buffer = (char *)std::malloc(fileSize + 1);

    if (buffer == nullptr) {
        std::perror("[MEM] Memory allocation failed");
        std::fclose(file);
        return false;
    }

    std::fread(buffer, fileSize, 1, file);
    buffer[fileSize] = '\0';

    std::rewind(file);
    std::fprintf(file, "/*************************************************\
*****************************");
    std::fprintf(file, "\n * PROGRAM \t%s", this->_dataset.program);
    std::fprintf(file, "\n * FILE    \t%s", this->_dataset.filename);
    std::fprintf(file, "\n * AUTHOR  \t%s", this->_dataset.author);
    std::fprintf(file, "\n * DATE    \t%s", this->_dataset.date);
    std::fprintf(file, "\n * LANGUAGE\t%s", this->_dataset.language);
    std::fprintf(file, "\n **************************************************\
***************************/\n\n");

    std::fwrite(buffer, fileSize, 1, file);

    std::free(buffer);
    std::fclose(file);

    return true;
}
