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

#include <QGraphicsDropShadowEffect>
#include <QMimeDatabase>
#include <QMimeType>
#include <QPalette>
#include <QApplication>
#include <QMessageBox>

#include "themefunc.h"
#include "cprime.h"
#include "settingsmanage.h"
#include "desktopfile.h"
#include "applicationdialog.h"

/*
 * Add shadow effect on a widget.
 */
void CPrime::ThemeFunc::addDropShadow(QWidget *widget, const int alpha, const QColor color, const int blur, const QString &styleSheet)
{
    SettingsManage sm;

    if (sm.getAddShadow()) {
        QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(widget);
        effect->setBlurRadius(blur);
        effect->setColor(QColor(color.red(), color.green(), color.blue(), alpha));
        effect->setOffset(0);

        widget->setGraphicsEffect(effect);

        if (styleSheet.count())
            widget->setStyleSheet(styleSheet);
    }
}

void CPrime::ThemeFunc::addDropShadow(QWidget *widget, const int alpha, const int blur, const QString &styleSheet)
{
    addDropShadow(widget, alpha, QColor(0, 0, 0), blur, styleSheet);
}

/*
 * Extract Icon from *.desktop file.
 */
QIcon CPrime::ThemeFunc::getAppIcon(const QString &appName)
{
    DesktopFile df = DesktopFile(CPrime::Variables::CC_System_AppPath() + appName + ".desktop");
    return (ApplicationDialog::searchAppIcon(df));
}

/*
 * Extract Icon from mime database.
 */
QIcon CPrime::ThemeFunc::getFileIcon(const QString &filePath)
{
    QFileInfo info(filePath);

    if (filePath.count() == 0 || !info.exists()) {
        return QApplication::style()->standardIcon(QStyle::SP_FileIcon);
    }

    QIcon icon;
    QMimeDatabase mimedb;
    QMimeType mimeType;

    mimeType = mimedb.mimeTypeForFile(filePath);
    icon = QIcon::fromTheme(mimeType.iconName());

    if (icon.isNull()) {
        return QApplication::style()->standardIcon(QStyle::SP_FileIcon);;
    }

    return icon;
}

QSettings *CPrime::ThemeFunc::getStyleSheet()
{
    SettingsManage sm;
    QSettings *m_StyleSheet = nullptr;
    QString appThemePath = nullptr;

    // Load View Mode
    if (sm.getStyleMode()) {
        appThemePath = QString("%1/modeLight.ini").arg(COREAPPS_THEME_FOLDER);
    } else {
        appThemePath = QString("%1/modeDark.ini").arg(COREAPPS_THEME_FOLDER);
    }

    m_StyleSheet = new QSettings(appThemePath, QSettings::IniFormat);

    return m_StyleSheet;
}

QString CPrime::ThemeFunc::getStyleSheetFileContent(CPrime::StyleTypeName s)
{
    QString path = nullptr;

    QString argPath = QString("%1").arg(COREAPPS_THEME_FOLDER) + "/%1.qss";
    switch (s) {
    case CPrime::StyleTypeName::AboutStyle:
        path = argPath.arg("About");
        break;
    case CPrime::StyleTypeName::BookmarkItStyle:
        path = argPath.arg("BookmarkIt");
        break;
    case CPrime::StyleTypeName::BookmarksStyle:
        path = argPath.arg("Bookmarks");
        break;
    case CPrime::StyleTypeName::CoreActionStyle:
        path = argPath.arg("CoreAction");
        break;
    case CPrime::StyleTypeName::CoreArchiverStyle:
        path = argPath.arg("CoreArchiver");
        break;
    case CPrime::StyleTypeName::CoreBoxStyle:
        path = argPath.arg("CoreBox");
        break;
    case CPrime::StyleTypeName::CoreFMStyle:
        path = argPath.arg("CoreFM");
        break;
    case CPrime::StyleTypeName::CoreImageStyle:
        path = argPath.arg("CoreImage");
        break;
    case CPrime::StyleTypeName::CorePadStyle:
        path = argPath.arg("CorePad");
        break;
    case CPrime::StyleTypeName::CorePaintStyle:
        path = argPath.arg("CorePaint");
        break;
    case CPrime::StyleTypeName::CorePlayerStyle:
        path = argPath.arg("CorePlayer");
        break;
    case CPrime::StyleTypeName::CoreRenamerStyle:
        path = argPath.arg("CoreRenamer");
        break;
    case CPrime::StyleTypeName::CoreShotStyle:
        path = argPath.arg("CoreShot");
        break;
    case CPrime::StyleTypeName::CoreTimeStyle:
        path = argPath.arg("CoreTime");
        break;
    case CPrime::StyleTypeName::DashBoardStyle:
        path = argPath.arg("DashBoard");
        break;
    case CPrime::StyleTypeName::DialogStyle:
        path = argPath.arg("Dialog");
        break;
    case CPrime::StyleTypeName::HelpStyle:
        path = argPath.arg("Help");
        break;
    case CPrime::StyleTypeName::PropertiesStyle:
        path = argPath.arg("Properties");
        break;
    case CPrime::StyleTypeName::SearchStyle:
        path = argPath.arg("Search");
        break;
    case CPrime::StyleTypeName::SettingsStyle:
        path = argPath.arg("Settings");
        break;
    case CPrime::StyleTypeName::StartStyle:
        path = argPath.arg("Start");
        break;
    }

    QSettings *mStyleValues = nullptr;
    QString mStylesheetFileContent = nullptr;

    mStyleValues = getStyleSheet();
    mStylesheetFileContent = readStringFromFile(QString(path),QIODevice::ReadOnly);

    // set values example: @color01 => #fff
    for (const QString &key : mStyleValues->allKeys()) {
        mStylesheetFileContent.replace(key, mStyleValues->value(key).toString());
    }

    return mStylesheetFileContent;

//    @color01=apps mainWidget Color
//    @color02=dialogBox Color
//    @color03=apps topBar Color
//    @color04=highLight Color
//    @color05=border Color
//    @color06=apps seconderyWidget Color
//    @color07=apps text Color
//    @color08=apps HightlightText color
//    @color09=apps sidebarText color
}

QString CPrime::ThemeFunc::readStringFromFile(const QString &path, QIODevice::OpenMode mode)
{
    QSharedPointer<QFile> file(new QFile(path));
    QString data = nullptr;

    if (file->open(mode)) {
        data = file->readAll();
        file->close();
    } else {
        QMessageBox::warning(nullptr, "PROBLEM", path + " not found for theme.", QMessageBox::Ok);
    }

    return data;
}
