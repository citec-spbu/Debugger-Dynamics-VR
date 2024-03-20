#pragma once
#include <filesystem>
#include <vector>
#include <unordered_map>


class FileProtocol
{
public:
    // maybe more ctors in future
    FileProtocol() = default;
    FileProtocol(const std::string& pathIn, const std::string& pathOut);

    bool setInFile(const std::string& path);
    bool setOutFile(const std::string& path);
    bool getStatus() const;

    using param_t = std::pair<std::string, double>;

    // standart protocol procedure
    std::vector<param_t> exchange();

    // send request to get full set of params
    void sendRequestForAllParams();

    void changeParam(const std::string& param_name, double param_value);

private:

    std::unordered_map<std::string, double> m_change_buffer;
    std::filesystem::path m_fin;
    std::filesystem::path m_fout;
    bool m_all_params_requested = 0;
};