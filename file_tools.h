#pragma once
#include "lib_mac.h"

void clear_file(HANDLE& handle);

void unlock_both_files(HANDLE& infile, HANDLE& outfile);

bool file_empty(HANDLE& handle);

bool lock_both_files(HANDLE& infile, HANDLE& outfile);

std::string get_path_dir(char* full_path);

HANDLE open_file(std::string path);
