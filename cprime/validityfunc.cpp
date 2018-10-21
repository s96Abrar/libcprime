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

#include <QFileInfo>
#include "validityfunc.h"
#include "mimeutils.h"

QString CPrime::ValidityFunc::checkIsValidDir(const QString &path)
{
    if (path.count()) {
        QFileInfo dir(path);
        if (dir.isDir()) {
            if (dir.isRoot()) {
                return path;
            } else {
                if (path.endsWith('/')) {
                    return QString(path).remove(path.length() - 1, 1);
                } else {
                    return path;
                }
            }
        }
    } else {
        return nullptr;
    }
    return nullptr;
}

QString CPrime::ValidityFunc::checkIsValidFile(const QString &file)
{
    if (file.count()) {
        QFileInfo fi(file);
        if (fi.isFile()) {
            return file;
        }
    } else {
        return nullptr;
    }
    return nullptr;
}

bool CPrime::ValidityFunc::setupFileFolder(CPrime::FileFolderSetup fs)
{
    bool status = false;
    switch (fs) {
        case CPrime::BookmarkFolder: {
            if (!QDir(CPrime::Variables::CC_CoreApps_ConfigDir()).exists()) {
                status = QDir::home().mkdir(".config/coreBox");
            } else {
                status = true;
            }
            break;
        }
        case CPrime::DriveMountFolder: {
            if (!QDir(CPrime::Variables::CC_CoreApps_MountDir()).exists()) {
                status = QDir::home().mkdir(".coreBox");
            } else {
                status = true;
            }
            break;
        }
        case CPrime::MimeFile: {
            if (!QFile(CPrime::Variables::CC_CoreApps_MimeFilePath()).exists()) {
                MimeUtils *mimeUtils = new MimeUtils;
                mimeUtils->setDefaultsFileName(CPrime::Variables::CC_CoreApps_MimeFilePath());
            }
            status = true;
            break;
        }
        case CPrime::TrashFolder: {
            if (!QDir(CPrime::Variables::CC_Home_TrashDir()).exists()) {
                QDir trash = QDir::home();
                status = trash.cd(".local/share/");
                status = trash.mkdir("Trash");
                status = trash.cd("Trash");
                status = trash.mkdir("files");
                status = trash.mkdir("info");
            } else {
                status = true;
            }
            break;
        }
    }

    return status;
}


// This function is in building do not use it.
void CPrime::ValidityFunc::checkTextWidgetPath(QLineEdit *m_t)
{
    QString m_text = m_t->text();
    QFileInfo m_info(m_text);

    if (m_info.exists()) {

    }

}
