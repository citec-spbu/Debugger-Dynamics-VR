#include "file_tools.h"

bool file_empty(HANDLE& handle) {
	return !GetFileSize(handle, NULL);
}

void clear_file(HANDLE& handle) {
	SetFilePointer(handle, 0, 0, FILE_BEGIN);
	SetEndOfFile(handle);
}

void unlock_both_files(HANDLE& infile, HANDLE& outfile) {
    UnlockFile(infile, 0, 0, MAXDWORD, MAXDWORD);
    UnlockFile(outfile, 0, 0, MAXDWORD, MAXDWORD);
}

bool lock_both_files(HANDLE& infile, HANDLE& outfile) {
    if (LockFile(infile, 0, 0, MAXDWORD, MAXDWORD)) {

        if (LockFile(outfile, 0, 0, MAXDWORD, MAXDWORD))
            return true;
        
        UnlockFile(infile, 0, 0, MAXDWORD, MAXDWORD);
    }
    return false;
}

std::string get_path_dir(char* full_path) {
    std::string path;
    char line[MAX_PATH];
    _splitpath(full_path, NULL, line, NULL, NULL);
    return std::string(line);
}

HANDLE open_file(std::string path) {
    HANDLE file = CreateFileA(path.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    /*
    if (file == INVALID_HANDLE_VALUE) {
        std::cout << path + " opening error!";
        exit(1);
    }
    */

    return file;
}