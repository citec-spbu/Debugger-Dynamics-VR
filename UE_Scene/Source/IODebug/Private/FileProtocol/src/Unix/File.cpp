#ifdef __linux__

#include "../File.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <climits>

struct File::FileDescriptor
{
    int fd;
    FileDescriptor() = default;
    FileDescriptor(int fd) : fd(fd) {}
    operator int() const
    {
        return fd;
    }
};


File::File(const std::string& path) : m_fd(new FileDescriptor)
{
    *m_fd = open(path.c_str(), O_RDWR);
}


bool File::write(const std::string& buff)
{
    if (lseek(*m_fd, 0, SEEK_SET) == -1)
        return 0;

    return -1 != ::write(*m_fd, buff.c_str(), buff.size());
}


std::string File::read()
{
    struct stat st; 
    if (*m_fd == -1 || fstat(*m_fd, &st) || lseek(*m_fd, 0, SEEK_SET) == -1)
        return "";

    size_t sz = st.st_size;

    std::string buff(sz, 0);

    if (::read(*m_fd, buff.data(), sz) == -1)
        return "";

    return buff;
}


bool File::lock()
{
    if (lseek(*m_fd, 0, SEEK_SET) == -1 || lockf(*m_fd, F_TLOCK, INT_MAX) == -1)
        return 0;
    
    m_locked = 1;
    return 1;
}


void File::unlock()
{
    lseek(*m_fd, 0, SEEK_SET);
    lockf(*m_fd, F_ULOCK, INT_MAX);
    m_locked = 0;
}


bool File::isEmpty()
{
    if (*m_fd == -1)
        return 1;

    struct stat st;
    fstat(*m_fd, &st);

    return st.st_size == 0;
}


bool File::clear()
{
    return ftruncate(*m_fd, 0) == -1;
}


File::operator bool() const
{
    return *m_fd != -1;
}


File::~File()
{
    if (m_locked)
        unlock();

    if (*m_fd != -1)
        close(*m_fd);
}

#endif