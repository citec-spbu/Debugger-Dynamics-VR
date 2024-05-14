#include <FileProtocol.h>
#include <file_tools.h>
#include <data_tools.h>


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


std::vector<FileProtocol::param_t> FileProtocol::exchange()
{
    if (!getStatus())
        return {};

    /*
    int in_size = std::filesystem::file_size(m_fin);
    int out_size = std::filesystem::file_size(m_fout);

    if (!in_size || out_size)
        return {};
    */

    HANDLE hIn = open_file(m_fin.string());
    if (hIn == INVALID_HANDLE_VALUE)
        return {};

    HANDLE hOut = open_file(m_fout.string());
    if (hOut == INVALID_HANDLE_VALUE)
    {
        CloseHandle(hIn);
        return {};
    }

    if (!file_empty(hOut) || !lock_both_files(hIn, hOut))
    {
        CloseHandle(hIn);
        CloseHandle(hOut);
        return {};
    }

    // maybe add logging later
    // dummy handle for lvalue argument
    HANDLE dummy = NULL;

    // writing to out file
    if (m_all_params_requested)
    {
        DWORD written;

        if (WriteFile(hOut, " ", 1, &written, NULL))
            m_all_params_requested = 0;
    }
    else if (m_change_buffer.size() && print_data_in_outfile(hOut, dummy, m_change_buffer))
        m_change_buffer.clear();

    // reading changed params from in file
    std::unordered_map<std::string, double> changed_params;
    if (!file_empty(hIn) && read_data_from_infile(hIn, dummy, changed_params))
        clear_file(hIn);

    // ending up with resources
    unlock_both_files(hIn, hOut);
    CloseHandle(hIn);
    CloseHandle(hOut);

    // copying to result vector
    std::vector<param_t> result;
    result.reserve(changed_params.size());

    for (auto& param : changed_params)
        result.push_back(std::move(param));

    return result;
}



void FileProtocol::sendRequestForAllParams()
{
    m_all_params_requested = 1;
}