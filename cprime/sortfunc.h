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

#ifndef SORTFUNC_H
#define SORTFUNC_H

#include <QStringList>

#include "cprime.h"

namespace CPrime {

class SortFunc
{
public:
    static QStringList sortDate(const QStringList &dateList, CPrime::SortOrder s = CPrime::Ascending, const QString &format = "dd.MM.yyyy");
    static QStringList sortTime(const QStringList &timeList, CPrime::SortOrder s = CPrime::Ascending, const QString &format = "hh.mm.ss");
    static QStringList sortList(const QStringList &list, CPrime::SortOrder s = CPrime::Ascending);
    static QStringList sortDateTime(const QStringList &dateTimeList, CPrime::SortOrder s = CPrime::Ascending, const QString &format = "hh.mm.ss - dd.MM.yyyy");

};

}

#endif // SORTFUNC_H
