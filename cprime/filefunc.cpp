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

#include "filefunc.h"

QString CPrime::FileFunc::formatSize(const quint64 &size)
{
    QString total = nullptr;

    if (size >= TB)
        total = QString("%1TB").arg(QString::number(qreal(size) / TB, 'f', 2));
    else if (size >= GB)
        total = QString("%1GB").arg(QString::number(qreal(size) / GB, 'f', 2));
    else if (size >= MB)
        total = QString("%1MB").arg(QString::number(qreal(size) / MB, 'f', 1));
    else if (size >= KB)
        total = QString("%1KB").arg(QString::number(qreal(size) / KB,'f', 1));
    else
        total = QString("%1 bytes").arg(size);

    return total;
}
