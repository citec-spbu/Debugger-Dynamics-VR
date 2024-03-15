#include "data_tools.h"
#include "file_tools.h"

using namespace std;

void print_all_data(map<string, double>& data) {
    map<string, double> ::iterator it = data.begin();

    for (; it != data.end(); ++it) {
        cout << it->first << " = " << fixed << setprecision(6) << it->second << endl;
    }
}

void change_data(map<string, double>& data) {
	if (!data.empty())
		data[data.begin()->first] += 1;
}

char* data_in_chararr(map<string, double>& data) {
	stringstream strs;
	map<string, double> ::iterator it = data.begin();

	for (; it != data.end(); ++it) {
		strs << it->first << "=" << fixed << setprecision(6) << it->second << "\n";
	}

	const int length = strs.str().length();
	char* char_array = new char[length + 1];
	strcpy(char_array, strs.str().c_str());

	return char_array;
}

void chararr_push_in_data(char* line, int size_of_line, map<string, double>& data) {

	string paramName, paramValue;
	bool invalue = false;
	char chr;

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

bool print_data_in_outfile(HANDLE& outfile, HANDLE& logfile, map<string, double>& data) {
	_OVERLAPPED overlapped1 = { 0 };

	char* char_array = data_in_chararr(data);
	clear_file(outfile);

	if (!WriteFile(outfile, char_array, strlen(char_array), 0, &overlapped1)) {
		logging(logfile, "Error writing to the file!");
		cout << "Error writing to the file!" << endl;
		return false;
	}

	delete[] char_array;
	return true;
}

bool read_data_from_infile(HANDLE& infile, HANDLE& logfile, map<string, double>& data, bool with_clear) {

	SetFilePointer(infile, 0, 0, FILE_BEGIN);
	int size_of_file = GetFileSize(infile, NULL);
	char* line = new char[size_of_file];

	if (!ReadFile(infile, line, size_of_file, NULL, NULL)) {
		logging(logfile, "Error reading from the file!");
		cout << "Error reading from the file!" << endl;
		return false;
	}

	if (with_clear)
		data.clear();

	chararr_push_in_data(line, size_of_file, data);
	delete[] line;

	return true;
}

void get_data_from_config(string path, int& delay, HANDLE& logfile) {
	map <string, double> data;
	HANDLE config = open_file(path + "config.txt");

	if (file_empty(config)) {
		_OVERLAPPED overlapped1 = { 0 };
		string line = "delay=100";

		if (!WriteFile(config, line.c_str(), line.size(), 0, &overlapped1)) {
			logging(logfile, "Error writing to the config!");
			cout << "Error writing to the config!" << endl;
		}

		delay = 100;
	}
	else {
		read_data_from_infile(config, logfile, data);
		delay = (int)data["delay"];
	}

}

void get_data_from_startfile(string path, map<string, double>& data, HANDLE& logfile) {
	HANDLE startfile = open_file(path + "start.txt");

	if (file_empty(startfile)) {
		_OVERLAPPED overlapped1 = { 0 };
		string line = "SomeParams=0.000000\ntestParams=0.000001";
		data["SomeParams"] = 0.000000;
		data["testParams"] = 0.000001;

		if (!WriteFile(startfile, line.c_str(), line.size(), 0, &overlapped1)) {
			logging(logfile, "Error writing to the startfile!");
			cout << "Error writing to the startfile!" << endl;
		}
	}
	else {
		read_data_from_infile(startfile, logfile, data);
	}

	CloseHandle(startfile);
}

void logging(HANDLE& logfile, string info) {
	_OVERLAPPED overlapped1 = { 0 };
	overlapped1.Offset = MAXDWORD;
	overlapped1.OffsetHigh = MAXDWORD;

	SYSTEMTIME st;
	GetLocalTime(&st);

	stringstream strs;
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

	const int length = strs.str().length();
	char* char_array = new char[length + 1];
	strcpy(char_array, strs.str().c_str());

	if (!WriteFile(logfile, char_array, strlen(char_array), 0, &overlapped1)) {
		cout << "Error recording logs!" << endl;
		exit(1);
	}

	delete[] char_array;
}