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

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
#include <QDateTime>
#include <QApplication>
#include <QScreen>
#include <QSettings>

#include "settingsmanage.h"
#include "stringfunc.h"
#include "infofunc.h"
#include "themefunc.h"

/*
 * Return system screen size.
 */
QRect CPrime::InfoFunc::screenSize()
{
    QScreen *scr = QGuiApplication::primaryScreen();
    return scr->availableGeometry();
}

void CPrime::InfoFunc::messageEngine(const QString &message, CPrime::MessageType messageType, QWidget *parent)
{
    QWidget *mbox = new QWidget(parent);
    QLabel *l = new QLabel(message);
    QFont f ("Arial", 14, QFont::Bold);    
    QVBoxLayout *bi = new QVBoxLayout();
    QVBoxLayout *bii = new QVBoxLayout();
    QFrame *frame = new QFrame();

    frame->setStyleSheet("QFrame { border-radius: 5px; }");
    bii->addWidget(frame);
    frame->setLayout(bi);
    mbox->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::ToolTip);
    mbox->setAttribute(Qt::WA_TranslucentBackground);
    mbox->setMinimumSize(230, 50);
    mbox->setLayout(bii);
    l->setStyleSheet("QLabel { padding: 10px; }");
    l->setFont(f);
    l->setAlignment(Qt::AlignCenter);
    bi->addWidget(l);
    bi->setContentsMargins(0, 0, 0, 0);
    QString stylesheet;
    if (messageType == CPrime::MessageType::Info) {
        stylesheet = "QWidget { background-color: rgba(35, 35, 35, 200); color: #ffffff; border: 1px #2A2A2A; border-radius: 3px; }";
    } else if (messageType == CPrime::MessageType::Warning) {
        stylesheet = "QWidget { background-color: rgba(240, 0, 0, 150); color: #ffffff; border: 1px #2A2A2A; border-radius: 3px; }";
    } else if (messageType == CPrime::MessageType::Tips) {
        stylesheet = "QWidget { background-color: rgba(0, 0, 240, 150); color: #ffffff; border: 1px #2A2A2A; border-radius: 3px; }";
    } else {
        return;
    }

    mbox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    CPrime::ThemeFunc::addDropShadow(mbox, 60);
    mbox->setStyleSheet(stylesheet);
    mbox->show();

    int x = CPrime::InfoFunc::screenSize().width() - (mbox->width() + 5);
    int y = CPrime::InfoFunc::screenSize().height() - (mbox->height() + 5);
    mbox->move(x,y);

    QTimer::singleShot(3000, mbox, SLOT(close()));
}

QStringList CPrime::InfoFunc::fStringList(QStringList &left, QStringList &right, QFont font)
{
    QFontMetrics *fontM = new QFontMetrics(font);
    int large = 0;

    foreach (QString s, left) {
        if (large < fontM->width(s)) {
            large = fontM->width(s);
        }
    }

    large = large + fontM->width('\t');

    int index = 0;
    foreach (QString s, left) {
        while (large >= fontM->width(s)) {
            left.replace(index++, s + "\t");
        }
    }

    index = 0;
    foreach (QString s, left) {
        QString rFirstW = s.at(0).toUpper();
        QString rRestW  = s.right(s.length() - 1);
        left.replace(index, rFirstW + rRestW + ": " + right.at(index));
        index++;
    }

    return left;
}

QString CPrime::InfoFunc::sentDateText(const QString &dateTime)
{
    QDateTime given = QDateTime::fromString(dateTime, "dd.MM.yyyy");
    if (QDate::currentDate().toString("dd.MM.yyyy") == dateTime) {
        return QString("Today");
    } else {
        return QString(given.toString("MMMM dd"));
    }
}

bool CPrime::InfoFunc::saveToRecent(const QString &appName, const QString &pathName)
{
    SettingsManage sm;
    QString m_appName = CPrime::StringFunc::CapitalizeEachWord(appName);

    if (sm.getShowRecent()) { //true
        if (appName.count() && pathName.count()) {
            QSettings recentActivity(QDir::homePath() + "/.config/coreBox/RecentActivity", QSettings::IniFormat);
            QDateTime currentDT =  QDateTime::currentDateTime();
            QString group = currentDT.toString("dd.MM.yyyy");
            QString key = currentDT.toString("hh.mm.ss");
            recentActivity.beginGroup(group);
            recentActivity.setValue(key, m_appName + "\t\t\t" + pathName);
            recentActivity.endGroup();
            return true;
        }
    }

    return false;
}
