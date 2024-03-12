#include <map>
#include <string>
#include <fstream>
#include <optional>
#include <filesystem>
namespace Utility
{

class Config
{
private:
    std::map<std::string, std::string> params;
    std::fstream file;
    bool isGet = false;
public:
    Config() = default;
    Config(const std::string& path);
    std::optional<std::string> getParam(const std::string& arg);

    bool isCorrectRead();  
};
} // namespace