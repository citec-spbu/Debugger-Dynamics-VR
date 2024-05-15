#ifdef _WIN32

#include "../File.h"
#include <Windows.h>

struct File::FileDescriptor
{
    HANDLE handle;
    FileDescriptor() = default;
    FileDescriptor(HANDLE handle) : handle(handle) {}
    operator HANDLE() const
    {
        return handle;
    }
};

File::File(const std::string& path) : m_fd(new FileDescriptor)
{
    *m_fd = CreateFileA(path.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
}


bool File::write(const std::string& buff)
{
    SetFilePointer(*m_fd, 0, 0, FILE_BEGIN);

    return WriteFile(*m_fd, buff.c_str(), buff.size(), 0, NULL);
}


std::string File::read()
{
    SetFilePointer(*m_fd, 0, 0, FILE_BEGIN);

    int sz = GetFileSize(*m_fd, NULL);
    std::string buff(sz,0);

    if (!ReadFile(*m_fd, buff.data(), sz, NULL, NULL))
        return "";

    return buff;
}


bool File::lock()
{
    if (m_locked)
        return 1;

    if (!LockFile(*m_fd, 0, 0, MAXDWORD, MAXDWORD))
        return 0;
    
    m_locked = 1;
    return 1;
}


void File::unlock()
{
    if (!m_locked)
        return;
    
    UnlockFile(*m_fd, 0, 0, MAXDWORD, MAXDWORD);
    m_locked = 0;
}


bool File::isEmpty()
{
    if (!*this)
        return 1;

    return 0 == GetFileSize(*m_fd, NULL);
}


bool File::clear()
{
    SetFilePointer(*m_fd, 0, 0, FILE_BEGIN);

    return SetEndOfFile(*m_fd);
}


File::operator bool() const
{
    return *m_fd != INVALID_HANDLE_VALUE;
}


File::~File()
{
    if (m_locked)
        unlock();

    if (*m_fd != INVALID_HANDLE_VALUE)
        CloseHandle(*m_fd);
}

#endif