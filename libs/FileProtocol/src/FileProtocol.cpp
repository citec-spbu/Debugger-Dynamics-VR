#include <FileProtocol.h>


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