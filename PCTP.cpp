/*
Parameter change testing program
*/

#include "lib_mac.h"
#include "data_tools.h"
#include "file_tools.h"


void exit(HANDLE& infile, HANDLE& outfile, HANDLE& logfile, int res) {
    CloseHandle(infile);
    CloseHandle(outfile);
    CloseHandle(logfile);
    exit(res);
}


int main(int argc, char* argv[]){

    std::string path = get_path_dir(argv[0]);
    char input;
    int delay;
    bool print_update_info;
    std::map <std::string, double> data;

    CreateDirectoryA((path + "params").c_str(), NULL);

    HANDLE logfile = open_file(path + "log.txt");
    HANDLE infile = open_file(path + "params\\params_in.txt");
    HANDLE outfile = open_file(path + "params\\params_out.txt");

    get_data_from_config(path, delay, print_update_info, logfile);
    get_data_from_startfile(path, data, logfile);
    clear_file(logfile);
    clear_file(infile);
    clear_file(outfile);

    while (true) {
        if (file_empty(outfile) && !file_empty(infile) && lock_both_files(infile, outfile)) {

            if (read_data_from_infile(infile, logfile, data)) {
                logging(logfile, "The information was succsessfully read from the infile.");

                std::cout << std::endl << "All data inputs:" << std::endl;
                print_all_data(data);
                clear_file(infile);

                if (print_data_in_outfile(outfile, logfile, data)) {
                    logging(logfile, "The information has been succsessfully written to the outfile.");
                    std::cout << "All data puts:" << std::endl;
                    print_all_data(data);
                }
            }

            unlock_both_files(infile, outfile);
        }

        else {
            change_data(data);

            if (LockFile(outfile, 0, 0, MAXDWORD, MAXDWORD)) {
                if (print_data_in_outfile(outfile, logfile, data)) {
                    logging(logfile, "The information has been succsessfully updated to the outfile.");

                    if (print_update_info) {
                        std::cout << std::endl << "Update:" << std::endl;
                        print_all_data(data);
                    }
                }

                UnlockFile(outfile, 0, 0, MAXDWORD, MAXDWORD);
            }
        }

        sleep(delay);

        if (_kbhit())
        {
            input = _getch();
            if (input == 'q')
                exit(infile, outfile, logfile, 0);
        }
    }

    return 0;
}
