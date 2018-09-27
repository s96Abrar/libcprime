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

#pragma once

#ifndef BOOKMARKMANAGE_H
#define BOOKMARKMANAGE_H

#include <QWidget>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QSet>
#include <QList>
#include <QTextStream>
#include <QLineEdit>
#include <QDateTime>

#include "utilities.h"

#include "libcprime_global.h"


class LIBCPRIMESHARED_EXPORT BookmarkManage
{

public:
    bool addSection(QString sectionName);
    bool addBookmark(QString sectionName, QString bookmarkName, QString bookPath);

    QStringList getBookSections();
    QStringList getBookNames(QString sectionName);
    QString bookingTime(QString sectionName, QString bookmarkName);
    QString bookmarkPath(QString sectionName, QString bookmarkName);
    QString checkingBookName(QString sectionName, QString bookName);
    QString checkingBookPath(QString section, QString bookPath);
    QString checkingBookPathEx(QString bookPath);
    QString cbookName = "CoreBoxBook";
    QString cbookPath = QDir::homePath() + "/.config/coreBox";
    QString cbookFullPath = cbookPath + "/" + cbookName;

    void checkBook();
    void delSection(QString sectionName);
    void delBookmark(QString bookmarkName);
    void changeAll(QString oldSectionName, QString oldBookmarkName, QString sectionName, QString bookmarkName, QString bookmarkValue);
    void editbookmark(QString sectionName, QString bookmarkName, QString bookPath);
    void delbookmark(QString bookmarkName, QString section);

private:
    void createBook();
    void changeSection(QString oldSectionName, QString sectionName, QString bookmarkName, QString bookmarkValue);
    void changeBookmark(QString oldBookmarkName, QString sectionName, QString bookmarkName, QString bookmarkValue);

    QStringList keys();
    QString bookmarkValues(QString sectionName, QString bookmarkName);
    QString keyCount();

};

#endif // BOOKMARKMANAGE_H

