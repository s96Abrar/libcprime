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

#include <QDir>
#include <QSettings>
#include "cvariables.h"
#include "settingsmanage.h"

QString CPrime::Variables::CC_CoreApps_ConfigDir()
{
    return QString( QDir::homePath() + "/.config/coreBox" );
}

QString CPrime::Variables::CC_CoreApps_MountDir()
{
    return QString( QDir::homePath() + "/.coreBox" );
}

QString CPrime::Variables::CC_CoreApps_BookMarkFilePath()
{
    return QString( CC_CoreApps_ConfigDir() + "/" + CC_CoreApps_BookMarkFile() );
}

QString CPrime::Variables::CC_CoreApps_ConfigFile()
{
    SettingsManage sm;
    return sm.cSetting->fileName();
}

QString CPrime::Variables::CC_CoreApps_ConfigFilePath()
{
    return QString( CC_CoreApps_ConfigDir() + "/" + CC_CoreApps_ConfigFile() );
}

QString CPrime::Variables::CC_Home_TrashDir()
{
    return QString( QDir::homePath() + "/.local/share/Trash" );
}

QString CPrime::Variables::CC_CoreApps_MimeFilePath()
{
    return QString( CC_CoreApps_ConfigDir() + "/" + CC_CoreApps_MimeFile() );
}

QString CPrime::Variables::CC_CoreApps_RecentActFilePath()
{
    return QString( CC_CoreApps_ConfigDir() + "/" + CC_CoreApps_RecentActFile() );
}
