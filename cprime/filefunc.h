/*
A Library for CoreApps .

This file is part of libcprime.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

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
