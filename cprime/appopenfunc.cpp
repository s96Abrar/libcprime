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

#include "appopenfunc.h"


/*
 * Open app using QProcess with argument.
 * appName : must need to pass exact app name
 * N.B. There is no checking method to check whether the app name is correct.
 */
void CPrime::AppOpenFunc::systemAppOpener(const QString &appName, const QString &arg)
{
    bool status = false;
    if (arg.count()) {
        // FIX ME
        // appName must not need to convert to lowercase
        //
        QProcess::startDetached(appName.toLower(), QStringList() << arg);
    } else {
        QProcess::startDetached(appName.toLower());
    }

    if (status) {
        CPrime::InfoFunc::messageEngine(QString(appName + " opening"), CPrime::MessageType::Info, nullptr);
    }
}

/*
 * Catagorize a path with the extention to open on specific app
 * path : Need a specific pathCPrimeCPrime
 * processOwner : Object which responsible to open the app
 */
void CPrime::AppOpenFunc::appSelectionEngine(const QString &path, QObject *processOwner)
{
    QFileInfo file(path);
    if (!file.exists() || path.count() == 0) {
        CPrime::InfoFunc::messageEngine("File not exists...", CPrime::MessageType::Warning, static_cast<QWidget*>(processOwner));
        return;
    }

    QStringList image, text, pdf, media;
    image << "jpg" << "jpeg" << "png" << "ico" << "svg" << "gif";
    text  << "txt" << "pro" << "";
    pdf   << "pdf" << "xps" << "oxps" << "epub" << "cbr" << "cbz" << "cbt" << "cba" ;
    media << "webm" << "ogg" << "mpeg" << "mov" << "mkv" << "flv" << "avi"
          << "mp3" << "aac" << "m4a"  << "flac" << "mp4";

    QString suffix = file.suffix().toLower();

    if (file.isDir()) {
        appEngine(CPrime::Category::FileManager, file, processOwner);
    } else if (file.isFile()) {
        // Image Viewer
        if (image.contains(suffix, Qt::CaseInsensitive)) {
            appEngine(CPrime::Category::ImageViewer, file, processOwner);
        }
        // Text Editor
        else if (text.contains(suffix, Qt::CaseInsensitive)) {
            appEngine(CPrime::Category::TextEditor, file, processOwner);
        }
        // PDF Viewer
        else if (pdf.contains(suffix, Qt::CaseInsensitive)) {
            appEngine(CPrime::Category::PDFViewer, file, processOwner);
        }
        // Media Player
        else if (media.contains(suffix, Qt::CaseInsensitive)) {
            appEngine(CPrime::Category::MediaPlayer, file, processOwner);
        }
        // Send to System
        else {
            QProcess::startDetached("xdg-open", QStringList() << path);
        }
    }
}

/*
 * Open app (open the *.desktop file) based on category.
 */
void CPrime::AppOpenFunc::appEngine(CPrime::Category ctg, const QFileInfo &file, QObject *processOwner)
{
    SettingsManage sm;
    MimeUtils *mimeUtils = new MimeUtils;
    QString path(file.absoluteFilePath());

    switch (ctg) {
    case CPrime::Category::FileManager: {
        // Needs to be the *.desktop name
        QString defaultFileManager = sm.getFileManager(); // Selected File Manager
        QString appName = defaultFileManager/*.toLower()*/ + ".desktop";
        DesktopFile df = DesktopFile(CPrime::Variables::CC_System_AppPath() + appName);
        //        if (!QFileInfo("/usr/share/applications/" + appName).exists()) {
        //            Utilities::messageEngine(QString("Selected File Manager (%1) Not Found.").arg(appName), Utilities::MessageType::Warning);
        //            return;
        //        }
        mimeUtils->openInApp(df.getExec(), file, processOwner);

        // Show message
        CPrime::InfoFunc::messageEngine(defaultFileManager + " opening", CPrime::MessageType::Info, static_cast<QWidget*>(processOwner));

        // Save file to recent activity
        CPrime::InfoFunc::saveToRecent(defaultFileManager, path);
        break;
    }
    case CPrime::Category::TextEditor: {
        QString defaultTextEditor = sm.getTextEditor();
        QString appName = defaultTextEditor/*.toLower()*/ + ".desktop";
        DesktopFile df = DesktopFile(CPrime::Variables::CC_System_AppPath() + appName);
        mimeUtils->openInApp(df.getExec(), file, processOwner);

        // Show message
        QString mess = defaultTextEditor + " opening." ;
        CPrime::InfoFunc::messageEngine(mess, CPrime::MessageType::Info, static_cast<QWidget*>(processOwner));

        // Save file to RecentActivity
        CPrime::InfoFunc::saveToRecent(defaultTextEditor, path);
        break;
    }
    case CPrime::Category::ImageViewer: {
        QString defaultImageViewer = sm.getImageViewer(); // selected ImageViewer name from settings.

        QString appName = defaultImageViewer/*.toLower()*/ + ".desktop";
        DesktopFile df = DesktopFile(CPrime::Variables::CC_System_AppPath() + appName);
        mimeUtils->openInApp(df.getExec(), file, processOwner);

        // Show message
        QString mess = defaultImageViewer + " opening.";
        CPrime::InfoFunc::messageEngine(mess, CPrime::MessageType::Info, static_cast<QWidget*>(processOwner));

        // Save file to RecentActivity
        CPrime::InfoFunc::saveToRecent(defaultImageViewer,path);
        break;
    }
    case CPrime::Category::ImageEditor: {
        QString defaultImageEditor = sm.getImageEditor(); // selected ImageEditor name from settings.

        QString appName = defaultImageEditor/*.toLower()*/ + ".desktop";
        DesktopFile df = DesktopFile(CPrime::Variables::CC_System_AppPath() + appName);
        mimeUtils->openInApp(df.getExec(), file, processOwner);

        // Show message
        QString mess = defaultImageEditor + " opening.";
        CPrime::InfoFunc::messageEngine(mess, CPrime::MessageType::Info, static_cast<QWidget*>(processOwner));

        // Save file to RecentActivity
        CPrime::InfoFunc::saveToRecent(defaultImageEditor, path);
        break;
    }
    case CPrime::Category::MediaPlayer: {
        QString defaultMediaPlayer = sm.getMediaPlayer(); // selected ImageEditor name from settings.

        QString appName = defaultMediaPlayer/*.toLower()*/ + ".desktop";
        DesktopFile df = DesktopFile(CPrime::Variables::CC_System_AppPath() + appName);
        mimeUtils->openInApp(df.getExec(), file, processOwner);

        // Show message
        QString mess = defaultMediaPlayer + " opening.";
        CPrime::InfoFunc::messageEngine(mess, CPrime::MessageType::Info, static_cast<QWidget*>(processOwner));

        // Save file to RecentActivity
        CPrime::InfoFunc::saveToRecent(defaultMediaPlayer, path);
        break;
    }
    case CPrime::Category::PDFViewer: {
        QString defaultPDFViwer = sm.getPDFVierwer(); // selected ImageEditor name from settings.

        QString appName = defaultPDFViwer/*.toLower()*/ + ".desktop";
        DesktopFile df = DesktopFile(CPrime::Variables::CC_System_AppPath() + appName);
        mimeUtils->openInApp(df.getExec(), file, processOwner);

        // Show message
        QString mess = defaultPDFViwer + " opening.";
        CPrime::InfoFunc::messageEngine(mess, CPrime::MessageType::Info, static_cast<QWidget*>(processOwner));

        // Save file to RecentActivity
        CPrime::InfoFunc::saveToRecent(defaultPDFViwer, path);
        break;
    }
    case CPrime::Category::Terminal: {
        QString defaultTerminal = sm.getTerminal(); // selected terminal name from settings.
//        QStringList args(defultTerminal.split(" "));
//        QString name = args.at(0);
//        args.removeAt(0);

        QString appName = defaultTerminal + ".desktop";
        DesktopFile df = DesktopFile(CPrime::Variables::CC_System_AppPath() + appName);
        mimeUtils->openInApp(df.getExec(), file, processOwner);

        // Show message
        QString mess = defaultTerminal + " opening.";
        CPrime::InfoFunc::messageEngine(mess, CPrime::MessageType::Info, static_cast<QWidget*>(processOwner));

        break;
    }
    }
}
