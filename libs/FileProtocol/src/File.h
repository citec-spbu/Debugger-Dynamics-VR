#pragma once
#include <string>
#include <memory>

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

    operator bool() const;

    ~File();

private:
    
    struct FileDescriptor;
    std::unique_ptr<FileDescriptor> m_fd;
    bool m_locked = 0;
};