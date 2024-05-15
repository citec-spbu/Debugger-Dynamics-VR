#include "data_tools.h"


/**
* Write the data to unordered_map from char* using our structural file
* If KEY == " " - It says about request all params
**/
void chararr_push_in_data(char* line, int size_of_line, std::unordered_map<std::string, double>& data) {

	std::string paramName, paramValue;
	bool invalue = false;
	char chr;

	/**
	* Add a new functional to function
	**/
	if (line[0] == ' ') 
	{
		data[" "] = 0;
	}

	for (int i = 0; i <= size_of_line; ++i) {
		chr = line[i];
		if (chr == '\n' || i == size_of_line) {
			if (paramName != "")
				data[paramName] = (double)atof(paramValue.c_str());
			paramName = "", paramValue = "";
			invalue = false;
			continue;
		}
		if (chr == '=') {
			invalue = true;
			continue;
		}
		if (chr == ' ')
			continue;
		if (invalue)
			paramValue.push_back(chr);
		else
			paramName.push_back(chr);
	}
}


std::string data_in_chararr(std::unordered_map<std::string, double>& data) {
	std::stringstream strs;
	std::unordered_map<std::string, double> ::iterator it = data.begin();

	for (; it != data.end(); ++it) {
		strs << it->first << "=" << std::fixed << std::setprecision(6) << it->second << "\n";
	}

	const size_t length = strs.str().length();
	char* char_array = new char[length + static_cast <unsigned long long>(1)];

	return strs.str();
}