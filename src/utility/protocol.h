
#include <boost/interprocess/sync/file_lock.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/core/invoke_swap.hpp>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>

// MUST rewrite file reading and writing / locking 
namespace Utility
{
    
class IOFileProtocol
{
private:    
    std::string path_i;
    std::string path_o;
    std::ifstream input_s;
    std::ofstream output_s;
    boost::interprocess::file_lock input_lock;
    boost::interprocess::file_lock output_lock;
public:
    // Delete constructors, because file_lock isn't support multiple lock for one file
    IOFileProtocol(const IOFileProtocol&) = delete;
    IOFileProtocol& operator=(const IOFileProtocol&) = delete;

    IOFileProtocol() = default;
    IOFileProtocol(IOFileProtocol&&);
    IOFileProtocol& operator=(IOFileProtocol&&);
    IOFileProtocol(const std::string& _path_i, const std::string& _path_o);
    bool isOkey();

    std::optional<std::vector<std::string>> exchange(const std::vector<std::string>& data);

};
} // namespace