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

#include "stringfunc.h"


QString CPrime::StringFunc::CapitalizeEachWord(const QString &str)
{
    if (str.count() == 0)
        return nullptr;

    QStringList sep = str.split(' ');
    QString total = "";
    foreach (QString s, sep) {
        if (!s.count())
            continue;

        foreach (QChar c, s) {
            if (c.isLetter()) {
                s = s.toLower().replace(s.indexOf(c), 1, c.toTitleCase());
                break;
            }
        }
        total = total + " " + s;
    }

    return total.remove(0, 1);
}


QStringList CPrime::StringFunc::fStringList(QStringList &left, QStringList &right, QFont font)
{
    QFontMetrics *fontM = new QFontMetrics(font);
    int large = 0;

    foreach (QString s, left) {
        if (large < fontM->width(s)) {
            large = fontM->width(s);
        }
    }

    large = large + fontM->width('\t');

    int index = 0;
    foreach (QString s, left) {
        while (large >= fontM->width(s)) {
            left.replace(index++, s + "\t");
        }
    }

    index = 0;
    foreach (QString s, left) {
        QString rFirstW = s.at(0).toUpper();
        QString rRestW  = s.right(s.length() - 1);
        left.replace(index, rFirstW + rRestW + ": " + right.at(index));
        index++;
    }

    return left;
}
