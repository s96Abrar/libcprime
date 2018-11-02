#include <QMessageBox>
#include <QDateTime>
#include <QDebug>
#include "trashmanager.h"
#include "cprime.h"
#include "themefunc.h"
#include "infofunc.h"

QString CPrime::TrashManager::homeTrashLocation() {

    /* If the permissions of Trash folder are right; we assume $trash/files and $trash/info exists */
    QFileInfo assume(QDir::homePath());
    if (assume.exists() && assume.permission( QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner))
        return CPrime::Variables::CC_Home_TrashDir();
    else {
        /* Try to make the trash folder */
        QDir::home().mkpath("/.local/share/Trash/");
        QDir::home().mkpath("/.local/share/Trash/files/");
        QDir::home().mkpath("/.local/share/Trash/info/");
        QFile::setPermissions(CPrime::Variables::CC_Home_TrashDir(), QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner );

        return (CPrime::Variables::CC_Home_TrashDir() + "/");
    }
}

QString CPrime::TrashManager::trashLocation(const QString &path)
{
    // Ideally, if path is inside home.
    if (path.startsWith(QDir::homePath() + "/")) {
        return homeTrashLocation();
    } else {
        // If path is inside a extrenal device
        /*
         * NBDeviceInfo trashDevInfo = NBDeviceManager::deviceInfoForPath( path );

            QString mountPoint = trashDevInfo.mountPoint();

            // If the mount point does not exist, return a NULL string
            if ( access( mountPoint.toLocal8Bit().data(), R_OK | W_OK | X_OK ) )
                return QString();

            // If $MNTPT/.Trash/$UID is present, and accessible with right permissions
            // We blindly try to make $MTPT/.Trash/$uid/files, $MTPT/.Trash/$uid/info
            if( access( ( mountPoint + "/.Trash/" + QString::number( getuid() ) ).toLocal8Bit().data(), R_OK | W_OK | X_OK ) == 0 ) {
                QDir( mountPoint ).mkpath( QString( ".Trash/%1/" ).arg( getuid() ) );
                QDir( mountPoint ).mkpath( QString( ".Trash/%1/files/" ).arg( getuid() ) );
                QDir( mountPoint ).mkpath( QString( ".Trash/%1/info/" ).arg( getuid() ) );

                // Check if the any one above folders exist, say $MTPT/.Trash-$uid/files //
                if( access( ( mountPoint + "/.Trash/" + QString::number( getuid() ) + "/files/" ).toLocal8Bit().data(), R_OK | W_OK | X_OK ) == 0 )
                    return mountPoint + "/.Trash/" + QString::number( getuid() );

                return QString();
            }

            // Otherwise we create $MNTPT/.Trash-$UID
            QDir( mountPoint ).mkpath( QString( ".Trash-%1/" ).arg( getuid() ) );
            QDir( mountPoint ).mkpath( QString( ".Trash-%1/files/" ).arg( getuid() ) );
            QDir( mountPoint ).mkpath( QString( ".Trash-%1/info/" ).arg( getuid() ) );
            QFile::setPermissions( mountPoint + "/.Trash-" + QString::number( getuid() ), QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner );

            // Check if the any one above folders exist, say $MTPT/.Trash-$uid/files
            if( access( ( mountPoint + "/.Trash-" + QString::number( getuid() ) + "/files/" ).toLocal8Bit().data(), R_OK | W_OK | X_OK ) == 0 )
                return mountPoint + "/.Trash-" + QString::number( getuid() );

            return QString();
        }


         */
    }
    return QString();
}

bool CPrime::TrashManager::moveToTrash(const QStringList &filePaths)
{
    //failedList.clear();
    QStringList files(filePaths);
    //int count = 0;

    while (files.count()) {
        QString file = files.first();
        if (file.count()) {
            /*if (QFileInfo(file).size() >= 1073741824) {
                QMessageBox message(QMessageBox::Warning, "Warning!","File size is about 1 GB or larger.\nPlease delete it instead of moveing to trash.\nDo you want to delete it?", QMessageBox::No | QMessageBox::Yes);
                // FIX ME - Set a valid icon.
                //message.setWindowIcon(QIcon(":/app/icons/app-icons/CoreFM.svg"));
                message.setStyleSheet(CPrime::ThemeFunc::getStylesheetFileContent(CPrime::StyleTypeName::DialogStyle));

                int reply = message.exec();

                if (reply == QMessageBox::No) {
                    goto SEND_TO_TRASH;
                } else {
                    QFile::remove(fileName);
                }
            } else {
                SEND_TO_TRASH:*/

                QMessageBox message(QMessageBox::Warning, "Warning!", "Do you want to Trash the '" + file + "' ?", QMessageBox::No | QMessageBox::Yes);
                //FIX ME - Set a valid icon
                //message.setWindowIcon(QIcon(":/app/icons/app-icons/CoreFM.svg"));
                message.setStyleSheet(CPrime::ThemeFunc::getStyleSheetFileContent(CPrime::StyleTypeName::DialogStyle));

                int reply = message.exec();
                if (reply == QMessageBox::Yes) {
                    QString trashLoc = trashLocation(file);
                    //QDir trash(trashLoc);
                    QString newPath = trashLoc + "/files/" + QFileInfo(file).fileName();
                    QString delTime = QDateTime::currentDateTime().toString( "yyyy-MM-ddThh:mm:ss" );
                    // If it exists, add a date time to it to make it unique
                    if (QFileInfo(newPath).exists() && QFileInfo(newPath).permission(QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner))
                        newPath += delTime;

                    // Try trashing it. If it fails, intimate the user/
                    if (QFile(file).rename(newPath)) {
                        qDebug() << "Error" << errno << ": Failed to trash " << file << ":" << strerror( errno );
                        //failedList[count++] = file + "\t\t\tFailed to trash." ;
                    }

                    // If it succeeds, we write the meta data.
                    else {
                        QFile metadata( trashLoc + "/info/" + QFileInfo(file).fileName() + ".trashinfo" );
                        metadata.open( QIODevice::WriteOnly );
                        metadata.write(
                            QString(
                                "[Trash Info]\n"
                                "Path=%1\n"
                                "DeletionDate=%2\n"
                            ).arg( file ).arg( delTime ).toLocal8Bit()
                        );
                        metadata.close();
                    //QFile directorySizes(trash.path() + "/directorysizes");
                    //directorySizes.open(QFile::Append);
//                    QString fileLoaction = file;
//                    if (QFile(fileLoaction).exists()) {
//                        QFile(fileLocation).rename(trash.path() + "/files/" + QFileInfo(file).fileName());
//                    } else {
//                        QDir(QFileInfo(file).path()).rename(QFileInfo(file).fileName(), trash.path() + "/files/ " + QFileInfo(file).fileName());
//                    }

                    // Function from utilities.cpp
                    CPrime::InfoFunc::messageEngine("File Moved to Trash", CPrime::MessageType::Info, nullptr);


                }
                }
            //}
                    // .....
                    files.removeOne(file);
                    if (files.count()) {
                        continue;
                    } else {
                        return true;
                    }
                    //-----------
        } else {
            //failedList[count++] = file + "\t\t\tEmpty file path" ;
        }
    }

    return true;
}

void CPrime::TrashManager::restoreFromTrash(const QStringList &filenames) {
    QDir trash = QDir::home();
    trash.cd(".local/share/Trash");

    for (QString fileToRestore : filenames) {
        //Read Restore Info
        QFile info(trash.path() + "/info/" + fileToRestore + ".trashinfo");
        if (info.exists()) { //Sanity Check
            info.open(QFile::ReadWrite);
            QString moveTo = nullptr;

            for (QString line : QString(info.readAll()).split("\n")) {
                if (line.startsWith("Path=")) {
                    moveTo = line.split("=").at(1); //Read original file path
                }
            }

            if (moveTo.count()==0) { //Malformed info file
                qDebug() << "OP";
            } else {
                if (QFile(trash.path() + "/files/" + fileToRestore).exists()) { //Restore file
                    QFile(trash.path() + "/files/" + fileToRestore).rename(moveTo);
                    info.close();
                    info.remove();
                } else if (QDir(trash.path() + "/files/" + fileToRestore).exists()) { //Restore Directory
                    QDir(trash.path() + "/files").rename(fileToRestore, moveTo);
                    info.close();
                    info.remove();
                }
            }
        }
    }
}


/*
 *
bool CPrime::TrashManager::moveToTrash(const QStringList &fileNames)
{
    QStringList files(fileNames);

    while (files.count()) {
        QString file = files.first();
        if (file.count()) {
            if (QFileInfo(file).size() >= 1073741824) {
                QMessageBox message(QMessageBox::Warning, "Warning!","File size is about 1 GB or larger.\nPlease delete it instead of moveing to trash.\nDo you want to delete it?", QMessageBox::No | QMessageBox::Yes);
                message.setWindowIcon(QIcon(":/app/icons/app-icons/CoreFM.svg"));
                message.setStyleSheet(getStylesheetFileContent(StyleAppName::DialogStyle));

                int reply = message.exec();

                if (reply == QMessageBox::No) {
                    return false;
                } else {
                    QFile::remove(fileName);
                    return true;
                }
            } else {
                // Check the trash folder existence
                CPrime::ValidityFunc::setupFileFolder(CPrime::FileFolderSetup::TrashFolder);
                QDir trash(CPrime::CC_Home_TrashDir());
                QFile directorySizes(trash.path() + "/directorysizes");
                directorySizes.open(QFile::Append);

                QMessageBox message(QMessageBox::Warning, "Warning!", "Do you want to Trash the '" + fileName + "' ?", QMessageBox::No | QMessageBox::Yes);
                message.setWindowIcon(QIcon(":/app/icons/app-icons/CoreFM.svg"));
                message.setStyleSheet(CPrime::ThemeFunc::getStyleSheetFileContent(CPrime::StyleTypeName::DialogStyle));

                int reply = message.exec();
                if (reply == QMessageBox::Yes) {
                    QString fileLoaction = file;
                    if (QFile(fileLoaction).exists()) {
                        QFile(fileLocation).rename(trash.path() + "/files/" + QFileInfo(file).fileName());
                    } else {
                        QDir(QFileInfo(file).path()).rename(QFileInfo(file).fileName(), trash.path() + "/files/ " + QFileInfo(file).fileName());
                    }

                    QFile trashinfo(trash.path() + "/info/" + QFileInfo(file).fileName() + ".trashinfo");
                    trashinfo.open(QFile::WriteOnly);
                    trashinfo.write(QString("[Trash Info]\n").toUtf8());
                    trashinfo.write(QString("Path=" + fileLocation + "\n").toUtf8());
                    trashinfo.write(QString("DeletionDate=" + QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss") + "\n").toUtf8());
                    trashinfo.close();

                    // Function from utilities.cpp
                    CPrime::InfoFunc::messageEngine("File Moved to Trash", CPrime::MessageType::Info);

                    // .....
                    files.removeOne(file);
                    if (files.count()) {
                        continue;
                    } else {
                        return true;
                    }
                    //-----------
                }
            }
        }
    }
}
 *
 */
