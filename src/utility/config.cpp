#include "config.h"
namespace Utility
{      
Config::Config(const std::string& path)
{
    std::ifstream file(path);
    std::string buff;
    if(file.is_open())
    {
        while(std::getline(file, buff))
        {
            if(buff.size() > 0)
            {
                if(size_t index = buff.find("="); index != std::string::npos)  
                {
                    params[buff.substr(0,index)] = buff.substr(index+1,buff.size());                    
                }
                else
                {
                    return;
                }
            }
        }
    }
    else
    {
        return;
    }    
    isGet = true;
}

std::optional<std::string> Config::getParam(const std::string& arg)
{
    return params[arg];
}

bool Config::isCorrectRead()
{
    return isGet;
}  
} // namespace