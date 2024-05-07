#pragma once
#include <string>
#include <unordered_map>
#include <sstream>
#include <iomanip>

std::string data_in_chararr(std::unordered_map<std::string, double>& data);

void chararr_push_in_data(char* line, int size_of_line, std::unordered_map<std::string, double>& data);
