#ifndef FILEFUNC_H
#define FILEFUNC_H

#include <QString>

namespace CPrime {

class FileFunc
{
public:
    // File sizes in bytes.
    static const quint64 KB = 1024;
    static const quint64 MB = 1024 * KB;
    static const quint64 GB = 1024 * MB;
    static const quint64 TB = 1024 * GB;

    static QString formatSize(const quint64 &size);
};

}
#endif // FILEFUNC_H
