#include "protocol.h"
#include <iostream>
// Test protocol.cpp
int main()
{
    std::filesystem::create_directories(std::filesystem::path("test_files/"));

    std::ofstream file_i("test_files/test_i.txt"); // create file for writing in it
    file_i.close();

    std::ofstream file_o("test_files/test_o.txt"); // create file for reading from it
    file_o << "Test 1\n";
    file_o << "Test 2\n";
    file_o.close();

    Utility::IOFileProtocol ex("test_files/test_o.txt", "test_files/test_i.txt");
    auto result = ex.exchange({"Hi 1,,000","Im age"});    
    if(!result)
    {
        return 1; // Return 1 if don't take a data
    }
    for(int i = 1;i <= 2;i++)
    {   
        if((*result)[i-1] != "Test " + std::to_string(i))
        {
            return 2; // Return 2 if read is incorrect
        }
    }
    return 0;
}