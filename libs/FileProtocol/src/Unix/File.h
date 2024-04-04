#pragma once
#include <string>

// RAII file class wrapper
class File
{
public:

    File(const std::string& path);

    File(const File& another) = delete;
    File& operator=(const File& another) = delete;

    bool write(const std::string& buff);
    std::string read();

    bool lock();
    void unlock();

    bool isEmpty();
    bool clear();

    operator bool();

    ~File();

private:
    
    int m_fd = -1;
    bool m_locked = 0;
};