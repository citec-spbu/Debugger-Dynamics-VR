#include "data_tools.h"
#include "file_tools.h"

void print_all_data(std::unordered_map<std::string, double>& data) {
    std::unordered_map<std::string, double> ::iterator it = data.begin();

    for (; it != data.end(); ++it) {
        std::cout << it->first << " = " << std::fixed << std::setprecision(6) << it->second << std::endl;
    }
}

void change_data(std::unordered_map<std::string, double>& data) {
	if (!data.empty())
		data[data.begin()->first] += 1;
}

char* data_in_chararr(std::unordered_map<std::string, double>& data) {
	std::stringstream strs;
	std::unordered_map<std::string, double> ::iterator it = data.begin();

	for (; it != data.end(); ++it) {
		strs << it->first << "=" << std::fixed << std::setprecision(6) << it->second << "\n";
	}

	const size_t length = strs.str().length();
	char* char_array = new char[length + static_cast <unsigned long long>(1)];
	strcpy(char_array, strs.str().c_str());

	return char_array;
}
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

bool print_data_in_outfile(HANDLE& outfile, HANDLE& logfile, std::unordered_map<std::string, double>& data) {
	_OVERLAPPED overlapped1 = { 0 };

	char* char_array = data_in_chararr(data);
	clear_file(outfile);

	if (!WriteFile(outfile, char_array, (DWORD)strlen(char_array), 0, &overlapped1)) {
		logging(logfile, "Error writing to the file!");
		//std::cout << "Error writing to the file!" << std::endl;
		return false;
	}

	delete[] char_array;
	return true;
}

bool read_data_from_infile(HANDLE& infile, HANDLE& logfile, std::unordered_map<std::string, double>& data, bool with_clear) {

	SetFilePointer(infile, 0, 0, FILE_BEGIN);
	int size_of_file = GetFileSize(infile, NULL);
	char* line = new char[size_of_file];

	if (!ReadFile(infile, line, size_of_file, NULL, NULL)) {
		logging(logfile, "Error reading from the file!");
		//std::cout << "Error reading from the file!" << std::endl;
		return false;
	}

	if (with_clear)
		data.clear();

	chararr_push_in_data(line, size_of_file, data);
	delete[] line;

	return true;
}

void get_data_from_config(std::string path, int& delay, bool& print_update_info, HANDLE& logfile) {
	std::unordered_map <std::string, double> data;
	HANDLE config = open_file(path + "config.txt");

	if (file_empty(config)) {
		_OVERLAPPED overlapped1 = { 0 };
		std::string line = "delay=100\nprint_update_info=1";

		if (!WriteFile(config, line.c_str(), (DWORD)line.size(), 0, &overlapped1)) {
			logging(logfile, "Error writing to the config!");
			//std::cout << "Error writing to the config!" << std::endl;
		}

		delay = 100;
		print_update_info = 1;
	}
	else {
		read_data_from_infile(config, logfile, data);
		delay = (int)data["delay"];
		print_update_info = (bool)data["print_update_info"];
	}

}

void get_data_from_startfile(std::string path, std::unordered_map<std::string, double>& data, HANDLE& logfile) {
	HANDLE startfile = open_file(path + "start.txt");

	if (file_empty(startfile)) {
		_OVERLAPPED overlapped1 = { 0 };
		std::string line = "SomeParams=0.000000\ntestParams=0.000001";
		data["SomeParams"] = 0.000000;
		data["testParams"] = 0.000001;

		if (!WriteFile(startfile, line.c_str(), (DWORD)line.size(), 0, &overlapped1)) {
			logging(logfile, "Error writing to the startfile!");
			//std::cout << "Error writing to the startfile!" << std::endl;
		}
	}
	else {
		read_data_from_infile(startfile, logfile, data);
	}

	CloseHandle(startfile);
}

void logging(HANDLE& logfile, std::string info) {

	// maybe add logging later
	return;
	//
	_OVERLAPPED overlapped1 = { 0 };
	overlapped1.Offset = MAXDWORD;
	overlapped1.OffsetHigh = MAXDWORD;

	SYSTEMTIME st;
	GetLocalTime(&st);

	std::stringstream strs;
	if (st.wHour < 10)
		strs << '0';
	strs << st.wHour << ':';
	if (st.wMinute < 10)
		strs << '0';
	strs << st.wMinute << ':';
	if (st.wSecond < 10)
		strs << '0';
	strs << st.wSecond << '.';
	if (st.wMilliseconds < 100)
		strs << '0';
		if (st.wMilliseconds < 10)
			strs << '0';
	strs << st.wMilliseconds << ' ' << info << '\n';

	const size_t length = strs.str().length();
	char* char_array = new char[length + static_cast <unsigned long long>(1)];
	strcpy(char_array, strs.str().c_str());

	if (!WriteFile(logfile, char_array, (DWORD)strlen(char_array), 0, &overlapped1)) {
		//std::cout << "Error recording logs!" << std::endl;
		exit(1);
	}

	delete[] char_array;
}