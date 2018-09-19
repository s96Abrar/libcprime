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

#ifndef APPLICATIONDIALOG_H
#define APPLICATIONDIALOG_H

#include "desktopfile.h"

#include <QDialog>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QCompleter>
#include <QStringListModel>
#include <QDirIterator>

#include <cprime/utilities.h>

#include "libcprime_global.h"


class ApplicationDialog : public QDialog {

    Q_OBJECT

public:
    explicit ApplicationDialog(QWidget *parent = nullptr);
    QString getCurrentLauncher() const;
    QList<DesktopFile> getApplications();

    static QIcon searchAppIcon(const DesktopFile &app);
protected slots:
    void updateCommand(QTreeWidgetItem* current, QTreeWidgetItem* previous);

protected:
    QTreeWidget* appList;
    QLineEdit* edtCommand;
    DesktopFile result;
    QMap<QString, QStringList> catNames;
    QMap<QString, QTreeWidgetItem*> categories;
    QMap<QString, QTreeWidgetItem*> applications;
    QTreeWidgetItem* findCategory(const DesktopFile &app);
    void createCategories();

};

#endif // APPLICATIONDIALOG_H
