#include "protocol.h"
#include <iostream>
namespace Utility
{
// Constructors    
IOFileProtocol::IOFileProtocol(const std::string& _path_i, const std::string& _path_o)
{
    path_i = _path_i;
    path_o = _path_o;
    if(isOkey())
    {
        input_lock = boost::interprocess::file_lock(path_i.c_str());
        output_lock = boost::interprocess::file_lock(path_o.c_str());
    }
}

IOFileProtocol::IOFileProtocol(IOFileProtocol&& protocol)
{
    swap(input_s, protocol.input_s);
    swap(output_s, protocol.output_s);
    swap(path_o, protocol.path_o);
    swap(path_i, protocol.path_i);
    boost::core::invoke_swap(input_lock, protocol.input_lock);
    boost::core::invoke_swap(output_lock, protocol.output_lock);
}

IOFileProtocol& IOFileProtocol::operator=(IOFileProtocol&& protocol)
{
    swap(input_s, protocol.input_s);
    swap(output_s, protocol.output_s);
    swap(path_o, protocol.path_o);
    swap(path_i, protocol.path_i);
    boost::core::invoke_swap(input_lock, protocol.input_lock);
    boost::core::invoke_swap(output_lock, protocol.output_lock);
    return *this;
}
// Functions
bool IOFileProtocol::isOkey()
{
    if(std::filesystem::exists(path_i) && std::filesystem::exists(path_o))
    {
        return true;
    }
    return false;
}

std::optional<std::vector<std::string>> IOFileProtocol::exchange(const std::vector<std::string>& data)
{
    input_s.open(path_i);
    output_s.open(path_o, std::ios_base::app);
    if(!isOkey())
    {
        return std::nullopt;
    }
    std::vector<std::string> result;    
    // Locked section
    {
        // Input section
        std::string buff;        
        while (std::getline(input_s, buff))
        {
            result.push_back(std::move(buff));
        } 
        // Output section
        boost::interprocess::scoped_lock lock_o(output_lock);    
        output_s.seekp(0, std::ios_base::beg);
        for(const auto& item : data)
        {
            output_s << item << "\n";
        }
        output_s.flush();        
        // Clear input file (protocol rule)
        if(result.size() > 0)
        {
            boost::interprocess::scoped_lock lock_i(input_lock);
            std::filesystem::resize_file(path_i, 0);
        }
    }
    output_s.close();
    input_s.close();
    return result;
}
}// namespace