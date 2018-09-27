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

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QCompleter>
#include <QStringListModel>
#include <QDirIterator>
#include <QDebug>

#include "utilities.h"
#include "applicationdialog.h"

ApplicationDialog::ApplicationDialog(QWidget *parent) : QDialog(parent)
{
    // Title and size
//    this->setWindowIcon(QIcon(":/icons/CoreFM.svg"));
    this->setWindowTitle(tr("Select application"));
    this->setMinimumSize(320, 320);

    // set stylesheet from style.qrc
    setStyleSheet(Utilities::getStylesheetFileContent(Utilities::StyleAppName::DialogStyle));

    // Creates app list view
    appList = new QTreeWidget(this);
    appList->setIconSize(QSize(24, 24));
    appList->setFocusPolicy(Qt::NoFocus);
    appList->headerItem()->setText(0, tr("Application"));

    // Creates buttons
    QDialogButtonBox *buttons = new QDialogButtonBox(this);
    buttons->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttons, SIGNAL(rejected()), this, SLOT(reject()));

    // Command bar
    edtCommand = new QLineEdit(this);
    edtCommand->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QFormLayout* layoutCommand = new QFormLayout();
    layoutCommand->addRow(tr("Launcher: "), edtCommand);

    // Layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(appList);
    layout->addLayout(layoutCommand);
    layout->addWidget(buttons);

    // Synonyms for cathegory names
    catNames.clear();
    catNames.insert("Development", QStringList() << "Programming");
    catNames.insert("Games", QStringList() << "Game");
    catNames.insert("Graphics", QStringList());
    catNames.insert("Internet", QStringList() << "Network" << "WebBrowser");
    catNames.insert("Multimedia", QStringList() << "AudioVideo" << "Video");
    catNames.insert("Office", QStringList());
    catNames.insert("Other", QStringList());
    catNames.insert("Settings", QStringList() << "System");
    catNames.insert("Utilities", QStringList() << "Utility");


    // Create default application cathegories
    categories.clear();
    createCategories();

    // Load applications and create category tree list
    QList<DesktopFile> apps = ApplicationDialog::getApplications();

    foreach (DesktopFile app, apps) {

      // Check for name
      if (app.getName().compare("") == 0) {
        continue;
      }

      // Find category
      QTreeWidgetItem* category = findCategory(app);

      // Create item from current mime
      QTreeWidgetItem *item = new QTreeWidgetItem(category);
      item->setIcon(0, ApplicationDialog::searchAppIcon(app));
      item->setText(0, app.getName());
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

      // Register application
      applications.insert(app.getPureFileName(), item);
    }

    appList->setSortingEnabled(true);
    appList->sortByColumn(0, Qt::AscendingOrder);

    // Create completer and its model for editation of command
    QStringListModel* model = new QStringListModel(this);
    model->setStringList(applications.keys());
    QCompleter* completer = new QCompleter(this);
    completer->setModel(model);
    edtCommand->setCompleter(completer);

    // Signals
    connect(appList,
            SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
            SLOT(updateCommand(QTreeWidgetItem*,QTreeWidgetItem*)));
}

/**
 * @brief Searches for application icon in the filesystem
 * @param app
 * @param defaultIcon
 * @return icon
 */
QIcon ApplicationDialog::searchAppIcon(const DesktopFile &app)
{
    // Resulting icon
    QIcon icon;

    // First attempt, check whether icon is a valid file
    if (QFile(app.getIcon()).exists()) {
      icon = QIcon(app.getIcon());
      if (!icon.isNull()) {
        return icon;
      }
    }

    // Second attempt, try load icon from theme
    icon = QIcon::fromTheme(app.getIcon());
    if (!icon.isNull()) {
      return icon;
    }

    // Next, try luck with application name
    QString name = app.getFileName().remove(".desktop").split("/").last();
    icon = QIcon::fromTheme(name.toLower());
    if (!icon.isNull()) {
      return icon;
    }

    // Last chance
    QDir appIcons("/usr/share/pixmaps","", nullptr, QDir::Files | QDir::NoDotAndDotDot);
    QStringList iconFiles = appIcons.entryList();
    QStringList searchIcons = iconFiles.filter(name);
    if (searchIcons.count() > 0) {
      return QIcon("/usr/share/pixmaps/" + searchIcons.at(0));
    }

    QIcon iconnullptr(QIcon::fromTheme("application-x-executable"));

    // Default icon
    return iconnullptr;
}

/**
 * @brief Returns list of available applications
 * @return application list
 */
QList<DesktopFile> ApplicationDialog::getApplications()
{
    QList<DesktopFile> apps;
    QDirIterator it("/usr/share/applications", QStringList("*.desktop"),
                    QDir::Files | QDir::NoDotAndDotDot,
                    QDirIterator::Subdirectories);

    while (it.hasNext()) {
      it.next();
      apps.append(DesktopFile(it.filePath()));
    }

    return apps;
}

/**
 * @brief Returns currently selected launcher
 * @return currently selected launcher
 */
QString ApplicationDialog::getCurrentLauncher() const
{
    return edtCommand->text();
}

/**
 * @brief Creates default application categories
 * @param names names of cathegories with synonyms
 */
void ApplicationDialog::createCategories()
{
    // Create cathegories
    foreach (QString name, catNames.keys()) {

      // Find icon
      QIcon icon = QIcon::fromTheme("applications-" + name.toLower());

      // If icon not found, check synonyms
      if (icon.isNull()) {
        foreach (QString synonym, catNames.value(name)) {
          icon = QIcon::fromTheme("applications-" + synonym.toLower());
          break;
        }
      }

      // If icon still not found, retrieve default icon
      if (icon.isNull()) {
        icon = QIcon::fromTheme("application-x-executable");
      }

      // Create category
      QTreeWidgetItem* category = new QTreeWidgetItem(appList);
      category->setText(0, name);
      category->setIcon(0, icon);
      category->setFlags(Qt::ItemIsEnabled);
      categories.insert(name, category);
    }
}

/**
 * @brief Searches the most suitable category for application
 * @param app
 * @return cathegory
 */
QTreeWidgetItem* ApplicationDialog::findCategory(const DesktopFile &app)
{
    // Default categoty is 'Other'
    QTreeWidgetItem* category = categories.value("Other");

    // Try to find more suitable category
    foreach (QString name, catNames.keys()) {

      // Try cathegory name
      if (app.getCategories().contains(name)) {
        category = categories.value(name);
        break;
      }

      // Try synonyms
      bool found = false;
      foreach (QString synonym, catNames.value(name)) {
        if (app.getCategories().contains(synonym)) {
          found = true;
          break;
        }
      }
      if (found) {
        category = categories.value(name);
        break;
      }
    }
    return category;
}

/**
 * @brief Updates launcher command
 * @param current
 * @param previous
 */
void ApplicationDialog::updateCommand(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);
    edtCommand->setText(applications.key(current));
}
