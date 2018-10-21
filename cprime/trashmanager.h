#ifndef TRASHMANAGER_H
#define TRASHMANAGER_H

#include <QString>
#include <QStringList>

namespace CPrime {

class TrashManager
{
public:
    QStringList failedList;
    static QString homeTrashLocation();
    static QString trashLocation(const QString &path);
    static bool moveToTrash(const QStringList &filePaths);
    static void restoreFromTrash(const QStringList &filenames);
};

}

#endif // TRASHMANAGER_H
