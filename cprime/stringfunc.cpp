#include "stringfunc.h"

#include <QStringList>
#include <QChar>

QString StringFunc::CapitalizeEachWord(const QString &str)
{
    if (str.count() == 0)
        return NULL;

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
