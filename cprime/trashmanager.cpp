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

#include <QMessageBox>
#include <QDateTime>
#include <QDebug>
#include <QDir>

#include "trashmanager.h"
#include "cvariables.h"
#include "themefunc.h"
#include "infofunc.h"

QString CPrime::TrashManager::homeTrashLocation()
{
    /* If the permissions of Trash folder are right; we assume $trash/files and $trash/info exists */
    QFileInfo assume( QDir::homePath() );

    if ( assume.exists() && assume.permission( QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner ) ) {
        return CPrime::Variables::CC_Home_TrashDir();
    } else {
        QString trashDir = "/.local/share/Trash/";

        // Try to make the trash folder
        try {
            QDir::home().mkpath( trashDir );
            QDir::home().mkpath( trashDir + "files/" );
            QDir::home().mkpath( trashDir + "info/" );
            trashDir = QDir::homePath() + trashDir;
            QFile::setPermissions( trashDir, QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner );
        } catch ( ... ) {
            qDebug() << "Error " << errno << ": func(homeTrashLocation) : " << strerror( errno );
        }

        return trashDir;
    }
}

QString CPrime::TrashManager::trashLocation( const QString &path )
{
    // Ideally, if path is inside home.
    if ( path.startsWith( QDir::homePath() + "/" ) ) {
        return homeTrashLocation();
    } /*else {

        // If path is inside a extrenal device
        // We need to check the trash location.
    }*/

    return QString();
}

bool CPrime::TrashManager::moveToTrash( const QStringList &filePaths )
{
    //failedList.clear();
    QStringList files( filePaths );
    //int count = 0;

    while ( files.count() ) {
        QString file = files.first();

        if ( file.count() ) {
            if ( QFileInfo( file ).size() >= 1073741824 ) {
                QMessageBox message( QMessageBox::Warning, "Warning!", "File size is about 1 GB or larger.\nPlease delete it instead of moveing to trash.\nDo you want to delete it?",
                                     QMessageBox::No | QMessageBox::Yes );
                // FIX ME - Set a valid icon.
                //message.setWindowIcon(QIcon(":/app/icons/app-icons/CoreFM.svg"));
                message.setStyleSheet( CPrime::ThemeFunc::getStyleSheetFileContent( CPrime::StyleTypeName::DialogStyle ) );

                int reply = message.exec();

                if ( reply == QMessageBox::No ) {
                    goto SEND_TO_TRASH;
                } else {
                    QFile::remove( file );
                }
            } else {
SEND_TO_TRASH:

                QMessageBox message( QMessageBox::Warning, "Warning!", "Do you want to Trash the '" + file + "' ?", QMessageBox::No | QMessageBox::Yes );
                //FIX ME - Set a valid icon
                //message.setWindowIcon(QIcon(":/app/icons/app-icons/CoreFM.svg"));
                message.setStyleSheet( CPrime::ThemeFunc::getStyleSheetFileContent( CPrime::StyleTypeName::DialogStyle ) );

                int reply = message.exec();

                if ( reply == QMessageBox::Yes ) {
                    QString trashLoc = trashLocation( file );
                    //QDir trash(trashLoc);
                    QString newPath = trashLoc + "/files/" + QFileInfo( file ).fileName();
                    QString delTime = QDateTime::currentDateTime().toString( "yyyy-MM-ddThh:mm:ss" );

                    // If it exists, add a date time to it to make it unique
                    if ( QFileInfo( newPath ).exists() && QFileInfo( newPath ).permission( QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner ) ) {
                        newPath += delTime;
                    }

                    // Try trashing it. If it fails, intimate the user/
                    if ( !QFile( file ).rename( newPath ) ) {
                        qDebug() << "Error" << errno << ": Failed to trash " << file << ":" << strerror( errno );
                        //failedList[count++] = file + "\t\t\tFailed to trash." ;
                    }

                    // If it succeeds, we write the meta data.
                    else {
                        QFile metadata( trashLoc + "/info/" + QFileInfo( file ).fileName() + ".trashinfo" );
                        metadata.open( QIODevice::WriteOnly );
                        metadata.write(
                            QString(
                                "[Trash Info]\n"
                                "Path=%1\n"
                                "DeletionDate=%2\n"
                            ).arg( file ).arg( delTime ).toLocal8Bit()
                        );
                        metadata.close();

                        CPrime::InfoFunc::messageEngine( "File Moved to Trash", CPrime::MessageType::Info, nullptr );


                    }
                }

            }

            files.removeOne( file );
        } /*else {

        }*/
    }

    return true;
}

void CPrime::TrashManager::restoreFromTrash( const QStringList &filenames )
{
    QDir trash = QDir::home();
    trash.cd( ".local/share/Trash" );

    for ( QString fileToRestore : filenames ) {
        //Read Restore Info
        QFile info( trash.path() + "/info/" + fileToRestore + ".trashinfo" );

        if ( info.exists() ) { //Sanity Check
            info.open( QFile::ReadWrite );
            QString moveTo = nullptr;

            for ( QString line : QString( info.readAll() ).split( "\n" ) ) {
                if ( line.startsWith( "Path=" ) ) {
                    moveTo = line.split( "=" ).at( 1 ); //Read original file path
                }
            }

            if ( moveTo.count() == 0 ) { //Malformed info file
                qDebug() << "Error : func(restoreFromTrash) : Wrong info file.";
            } else {
                if ( QFile( trash.path() + "/files/" + fileToRestore ).exists() ) { //Restore file
                    QFile( trash.path() + "/files/" + fileToRestore ).rename( moveTo );
                    info.close();
                    info.remove();
                } else if ( QDir( trash.path() + "/files/" + fileToRestore ).exists() ) { //Restore Directory
                    QDir( trash.path() + "/files" ).rename( fileToRestore, moveTo );
                    info.close();
                    info.remove();
                }
            }
        }
    }
}
