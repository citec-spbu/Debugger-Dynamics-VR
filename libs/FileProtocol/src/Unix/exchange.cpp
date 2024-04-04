#include <FileProtocol.h>
#include <File.h>
#include <data_tools.h>


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