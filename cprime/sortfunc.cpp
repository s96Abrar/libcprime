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

#include <QDateTime>
#include <QCollator>

#include "sortfunc.h"

QStringList CPrime::SortFunc::sortDate(const QStringList &dateList, CPrime::SortOrder s, const QString &format)
{
    QStringList temp = dateList;

    QList<QDate> dates;

    foreach (QString str, temp) {
        dates.append(QDate::fromString(str, format));
    }

    std::sort(std::begin(dates), std::end(dates));

    if (s == CPrime::Ascending) {
        for (int i = 0; i < temp.count(); i++) {
            temp.replace(i, dates[i].toString(format));
        }
    } else {
        int reverse = temp.count() - 1;
        for (int i = 0; i < temp.count(); i++) {
            temp.replace(reverse, dates[i].toString(format));
            reverse--;
        }
    }

    dates.clear();

    return temp;
}

QStringList CPrime::SortFunc::sortTime(const QStringList &timeList, CPrime::SortOrder s, const QString &format)
{
    QStringList temp = timeList;

    QList<QTime> times;

    foreach (QString str, temp) {
        times.append(QTime::fromString(str, format));
    }

    std::sort(std::begin(times), std::end(times));

    if (s == CPrime::Ascending) {
        for (int i = 0; i < temp.count(); i++) {
            temp.replace(i, times[i].toString(format));
        }
    } else {
        int reverse = temp.count() - 1;
        for (int i = 0; i < temp.count(); i++) {
            temp.replace(reverse, times[i].toString(format));
            reverse--;
        }
    }

    times.clear();
    return temp;
}

QStringList CPrime::SortFunc::sortList(const QStringList &list, CPrime::SortOrder s)
{
    QStringList temp = list;
    QCollator sortNum;
    sortNum.setNumericMode(true);

    if (s == CPrime::Ascending) {
        std::sort(temp.begin(), temp.end(), sortNum);
    } else {
        std::sort(temp.begin(), temp.end(), [&sortNum](const QString &s1, const QString &s2) {
            return sortNum.compare(s1, s2) > 0;
        });
    }

    return temp;
}

QStringList CPrime::SortFunc::sortDateTime(const QStringList &dateTimeList, CPrime::SortOrder s, const QString &format)
{
    QStringList temp = dateTimeList;

    QList<QDateTime> dts;

    foreach (QString str, temp) {
        dts.append(QDateTime::fromString(str, format));
    }

    std::sort(std::begin(dts), std::end(dts));

    if (s == CPrime::Ascending) {
        for (int i = 0; i < temp.count(); i++) {
            temp.replace(i, dts[i].toString(format));
        }
    } else {
        int reverse = temp.count() - 1;
        for (int i = 0; i < temp.count(); i++) {
            temp.replace(reverse, dts[i].toString(format));
            reverse--;
        }
    }

    dts.clear();
    return temp;
}
