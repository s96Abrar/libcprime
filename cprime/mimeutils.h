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

#ifndef MIMEUTILS_H
#define MIMEUTILS_H

#include <QObject>
#include <QFileInfo>
#include <QProcess>
#include <QMimeDatabase>
#include <QMimeType>
#include <QTextStream>

#include "properties.h"
#include "desktopfile.h"
#include "libcprime_global.h"

/**
 * @class MimeUtils
 * @brief Helps with mime type management
 * @author Michal Rost
 * @date 29.4.2013
 */
class LIBCPRIMESHARED_EXPORT MimeUtils : public QObject {
  Q_OBJECT

public:
    explicit MimeUtils(QObject* parent = nullptr);
    virtual ~MimeUtils();
    void openInApp(const QFileInfo &file, QObject* processOwner = nullptr);
    void openInApp(QString exe, const QFileInfo &file, QObject* processOwner = nullptr);
    void setDefaultsFileName(const QString &fileName);
    void setDefault(const QString &mime, const QStringList &apps);
    QStringList getDefault(const QString &mime) const;
    QStringList getMimeTypes() const;
    QString getDefaultsFileName() const;
    static QList<DesktopFile> getApplications();

public slots:
    void generateDefaults();
    void saveDefaults();
    void loadDefaults();

private:
    bool defaultsChanged;
    QString defaultsFileName;
    Properties* defaults;

};

#endif // MIMEUTILS_H
