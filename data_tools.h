#pragma once
#include "lib_mac.h"

void print_all_data(std::map<std::string, double>& data);

void chararr_push_in_data(char* line, int size_of_line, std::map<std::string, double>& data);

void change_data(std::map<std::string, double>& data);

void get_data_from_startfile(std::string path, std::map<std::string, double>& data, HANDLE& logfile);

void get_data_from_config(std::string path, int& delay, bool& print_update_info, HANDLE& logfile);

void logging(HANDLE& logfile, std::string info);

bool read_data_from_infile(HANDLE& infile, HANDLE& logfile, std::map<std::string, double>& data, bool with_clear = false);

bool print_data_in_outfile(HANDLE& outfile, HANDLE& logfile, std::map<std::string, double>& data);

char* data_in_chararr(std::map<std::string, double>& data);