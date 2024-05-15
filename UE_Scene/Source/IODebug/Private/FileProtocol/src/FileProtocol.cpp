#include "../include/FileProtocol.h"
#include "File.h"
#include "data_tools.h"

FileProtocol::FileProtocol(const std::string& pathIn, const std::string& pathOut) :
    m_fin(pathIn),
    m_fout(pathOut)
    {}

bool FileProtocol::setInFile(const std::string& path)
{
    m_fin = std::filesystem::path{path};

    return std::filesystem::exists(m_fin);
}


bool FileProtocol::setOutFile(const std::string& path)
{
    m_fout = std::filesystem::path{path};

    return std::filesystem::exists(m_fout);
}


bool FileProtocol::getStatus() const
{
    return std::filesystem::exists(m_fin) && std::filesystem::exists(m_fout);
}


void FileProtocol::changeParam(const std::string& param_name, double param_value)
{
    m_change_buffer[param_name] = param_value;
}


void FileProtocol::sendRequestForAllParams()
{
    m_all_params_requested = 1;
}


std::vector<FileProtocol::param_t> FileProtocol::exchange()
{
    if (!getStatus())
        return {};

    File fin(m_fin.string());
    File fout(m_fout.string());

    if (!(fout.isEmpty() && fin.lock() && fout.lock()))
        return {};

    // writing 
    if (m_all_params_requested)
    {
        if (fout.write(" "))
            m_all_params_requested = 0;
    }
    else if (m_change_buffer.size() != 0 && fout.write(data_in_chararr(m_change_buffer)))
    {
        m_change_buffer.clear();
    }


    // reading
    if (fin.isEmpty())
        return {};

    std::string buffer = fin.read();
    std::unordered_map<std::string, double> changed_params;
    chararr_push_in_data(buffer.data(), buffer.size(), changed_params);
    fin.clear();


    // copying to result vector
    std::vector<param_t> result;
    result.reserve(changed_params.size());

    for (auto&& param : changed_params)
        result.push_back(param);

    return result;
}