/*
An Library for CoreApps .

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
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA*/

#include "globalfunctions.h"
#include <QDebug>

//bool checkRecentActivityFile()
//{
//    QFile file(QDir::homePath() + "/.config/coreBox/RecentActivity");
//    if (file.exists()) {
//        return true;
//    }
//    return false;
//}



// =========================================================================
#include <QString>
#include <QStringList>
#include "settingsmanage.h"
void GlobalFunc::appEngine(GlobalFunc::Category ctg , const QFileInfo &file,QObject *processOwner)
{
    SettingsManage sm;
    MimeUtils *mimeUtils = new MimeUtils();
    QString path(file.absoluteFilePath());

    switch (ctg) {

    case GlobalFunc::Category::FileManager: {

        QString defultFileManager = sm.getFileManager(); // selected FileManager name from settings.

        QString appName = defultFileManager/*.toLower()*/ + ".desktop";

//        if (defultFileManager == "Thunar") {
//           appName = defultFileManager + ".desktop";
//        }

        DesktopFile df = DesktopFile("/usr/share/applications/" + appName);
//        if (!QFileInfo("/usr/share/applications/" + appName).exists()) {
//            Utilities::messageEngine(QString("Selected File Manager (%1) Not Found.").arg(appName), Utilities::MessageType::Warning);
//            return;
//        }
        mimeUtils->openInApp(df.getExec(), file, processOwner);

        // Show message
        QString mess = defultFileManager + " opening " ;
        Utilities::messageEngine(mess, Utilities::MessageType::Info);

        // Save file to RecentActivity
        Utilities::saveToRecent(defultFileManager,path);

        break;
    }
    case GlobalFunc::Category::TextEditor: {

        QString defultTextEditor = sm.getTextEditor(); // selected TextEditor name from settings.

        QString appName = defultTextEditor.toLower() + ".desktop";
        DesktopFile df = DesktopFile("/usr/share/applications/" + appName);
        mimeUtils->openInApp(df.getExec(), file, processOwner);

        // Show message
        QString mess = defultTextEditor + " opening " ;
        Utilities::messageEngine(mess, Utilities::MessageType::Info);

        // Save file to RecentActivity
        Utilities::saveToRecent(defultTextEditor,path);

        break;
    }
    case GlobalFunc::Category::ImageViewer: {

        QString defultImageViewer = sm.getImageViewer(); // selected ImageViewer name from settings.

        QString appName = defultImageViewer.toLower() + ".desktop";
        DesktopFile df = DesktopFile("/usr/share/applications/" + appName);
        mimeUtils->openInApp(df.getExec(), file, processOwner);

        // Show message
        QString mess = defultImageViewer + " opening " ;
        Utilities::messageEngine(mess, Utilities::MessageType::Info);

        // Save file to RecentActivity
        Utilities::saveToRecent(defultImageViewer,path);

        break;
    }

    case GlobalFunc::Category::ImageEditor: {

        QString defultImageEditor = sm.getImageEditor(); // selected ImageEditor name from settings.

        QString appName = defultImageEditor.toLower() + ".desktop";
        DesktopFile df = DesktopFile("/usr/share/applications/" + appName);
        mimeUtils->openInApp(df.getExec(), file, processOwner);

        // Show message
        QString mess = defultImageEditor + " opening " ;
        Utilities::messageEngine(mess, Utilities::MessageType::Info);

        // Save file to RecentActivity
        Utilities::saveToRecent(defultImageEditor,path);

        break;
    }

    case GlobalFunc::Category::MediaPlayer: {

        QString defultMediaPlayer = sm.getMediaPlayer(); // selected ImageEditor name from settings.

        QString appName = defultMediaPlayer.toLower() + ".desktop";
        DesktopFile df = DesktopFile("/usr/share/applications/" + appName);
        mimeUtils->openInApp(df.getExec(), file, processOwner);

        // Show message
        QString mess = defultMediaPlayer + " opening " ;
        Utilities::messageEngine(mess, Utilities::MessageType::Info);

        // Save file to RecentActivity
        Utilities::saveToRecent(defultMediaPlayer,path);

        break;
    }


    case GlobalFunc::Category::PDFViwer: {

        QString defultPDFViwer = sm.getPDFVierwer(); // selected ImageEditor name from settings.

        QString appName = defultPDFViwer.toLower() + ".desktop";
        DesktopFile df = DesktopFile("/usr/share/applications/" + appName);
        mimeUtils->openInApp(df.getExec(), file, processOwner);

        // Show message
        QString mess = defultPDFViwer + " opening " ;
        Utilities::messageEngine(mess, Utilities::MessageType::Info);

        // Save file to RecentActivity
        Utilities::saveToRecent(defultPDFViwer,path);

        break;
    }

    case GlobalFunc::Category::Terminal: {

        QString defultTerminal = sm.getTerminal(); // selected terminal name from settings.
        QStringList args(defultTerminal.split(" "));
        QString name = args.at(0);
        args.removeAt(0);

        QString appName = defultTerminal + ".desktop";
        DesktopFile df = DesktopFile("/usr/share/applications/" + appName);
        mimeUtils->openInApp(df.getExec(), file, processOwner);

        // Show message
        QString mess = defultTerminal + " opening " ;
        Utilities::messageEngine(mess, Utilities::MessageType::Info);

        break;
    }

    }
}


#include <QString>
#include <QStringList>
void GlobalFunc::systemAppOpener(QString appName, const QString &arg) // engine to open app in window
{
    QProcess::startDetached(appName.toLower(), QStringList() << arg);

    // Show message
    QString mess = appName + " opening " ;
    Utilities::messageEngine(mess, Utilities::MessageType::Info);
}


void GlobalFunc::appSelectionEngine(const QString &path,QObject *processOwner) // engine send right file to coreapps or system
{
    QFileInfo file(path);
    if(!file.exists() || path.count() == 0){
        // Function from utilities.cpp
        Utilities::messageEngine("File not exists...", Utilities::MessageType::Warning);
        return;
    }

    QStringList image,txts,pdf,media;
    image << "jpg" << "jpeg" << "png" << "bmp" << "ico" << "svg" << "gif" ;
    txts << "txt" << "pro" << "" ;
    pdf << "pdf" << "xps" << "oxps" << "epub" << "cbr" << "cbz" << "cbt" << "cba" ;
    media << "webm" << "ogg" << "mpeg" << "mov" << "mkv" << "flv" << "avi"
           << "mp3" << "aac" << "m4a"  << "flac" << "mp4";

    QString suffix = QFileInfo(path).suffix();

    //File Manager
    if (file.isDir()) {
        GlobalFunc::appEngine(GlobalFunc::Category::FileManager, file, processOwner);
        return;
    }

    //Image Viewer
    else if (image.contains(suffix, Qt::CaseInsensitive)) {
        GlobalFunc::appEngine(GlobalFunc::Category::ImageViewer, file,processOwner);
        return;
    }

    //Text Editor
    else if (txts.contains(suffix, Qt::CaseInsensitive)) {
        GlobalFunc::appEngine(GlobalFunc::Category::TextEditor, file,processOwner);
        return;
    }

    //PDF Viewer
    else if (pdf.contains(suffix, Qt::CaseInsensitive)) {
        GlobalFunc::appEngine(GlobalFunc::Category::PDFViwer, file,processOwner);
        return;
    }

    //Media Player
    else if (media.contains(suffix, Qt::CaseInsensitive)) {
        GlobalFunc::appEngine(GlobalFunc::Category::MediaPlayer, file,processOwner);
        return;
    }

    //sendto System
    else {
        QProcess::startDetached("xdg-open", QStringList() << path);
    }
}






//void GlobalFunc::appEngines(GlobalFunc::AppsName i, const QString &arg) // engine to open app in window
//{
//    switch (i) {
//    case GlobalFunc::AppsName::CoreFM: {
//        corefm *app = new corefm();
//        QString str = Utilities::checkIsValidDir(arg);
//        if (!str.isEmpty() || !str.isNull()) app->goTo(str);
//        app->show();

//        break;
//    }
//    case GlobalFunc::AppsName::CoreImage: {
//        coreimage *app = new coreimage();
//        QString str = Utilities::checkIsValidFile(arg);
//        if (str.count())
//            app->loadFile(str);
//        app->show();

//        break;
//    }
//    case GlobalFunc::AppsName::CorePad: {
//        corepad *app = new corepad();
//        app->openText(Utilities::checkIsValidFile(arg));
//        app->show();

//        break;
//    }
//    case GlobalFunc::AppsName::CorePaint: {
//        corepaint *app = new corepaint();
//        const QString str = Utilities::checkIsValidFile(arg);
//        if (str.count()) app->initializeNewTab(true, str);
//        else app->initializeNewTab();
//        app->show();

//        break;
//    }
//    case GlobalFunc::AppsName::CorePlayer: {
//        coreplayer *app = new coreplayer();
//        const QString str = Utilities::checkIsValidFile(arg);
//        if (!str.isEmpty() || !str.isNull()) app->openPlayer(str);
//        app->show();

//        break;
//    }
//    case GlobalFunc::AppsName::Dashboard: {
//        dashboard *app = new dashboard();
//        app->show();

//        break;
//    }
//    case GlobalFunc::AppsName::Bookmarks: {
//        bookmarks *app = new bookmarks();
//        app->show();

//        break;
//    }
//    case GlobalFunc::AppsName::About: {
//        about *app = new about();
//        app->show();

//        break;
//    }
//    case GlobalFunc::AppsName::StartView: {
//        Start *app = new Start();
//        app->show();

//        break;
//    }
//    case GlobalFunc::AppsName::Help: {
//        help *app = new help();
//        app->show();

//        break;
//    }
//    case GlobalFunc::AppsName::Settings: {
//        settings *app = new settings();
//        app->show();

//        break;
//    }
//    case GlobalFunc::AppsName::Search: {
//        search *app = new search();
//        QString str = Utilities::checkIsValidDir(arg);
//        if (!str.isEmpty() || !str.isNull()) app->setPath(str);
//        app->show();

//        break;
//    }
//    case GlobalFunc::AppsName::CoreTime: {
//        coretime *app = new coretime();
//        app->show();

//        break;
//    }
//    case GlobalFunc::AppsName::CorePDF: {
//        corepdf *app = new corepdf();
//        const QString str = Utilities::checkIsValidFile(arg);
//        if (!str.isEmpty() || !str.isNull()) app->openPdfFile(str);
//        app->show();

//        break;
//    }
//    case GlobalFunc::AppsName::CoreTerminal: {
//        QString workDir = arg;
//        if (!arg.count())
//            workDir = QDir::homePath();
//        if (QFileInfo(workDir).isFile())
//            workDir = QFileInfo(arg).path();

//        coreterminal *cterm = new coreterminal( workDir, "" /*, Parent Needed */);
//        cterm->show();

//        break;
//    }
//    case GlobalFunc::AppsName::CoreRenamer: {
//        corerenamer *app = new corerenamer();
//        const QString str = Utilities::checkIsValidDir(arg);
//        if (str.count()) app->addPath(str);
//        app->show();

//        break;
//    }
//    default:
//        break;
//    }
//}





