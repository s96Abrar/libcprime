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

#ifndef CPRIME_H
#define CPRIME_H

#include <QDir>

#include "settingsmanage.h"

namespace CPrime {

class Variables {
public:
    // Returns the Configuration folder path
    static QString CC_CoreApps_ConfigDir() {
        return QString(QDir::homePath() + "/.config/coreBox");
    }

    // Returns the temporary mount folder path
    static QString CC_CoreApps_MountDir() {
        return QString(QDir::homePath() + "/.coreBox");
    }

    // Returns the Bookmark file name
    static QString CC_CoreApps_BookMarkFile() {
        return "CoreBoxBook";
    }

    // Returns the Bookmark file path
    static QString CC_CoreApps_BookMarkFilePath() {
        return QString(CC_CoreApps_ConfigDir() + "/" + CC_CoreApps_BookMarkFile());
    }

    // Returns the config file
    static QString CC_CoreApps_ConfigFile() {
        SettingsManage sm;
        return sm.cSetting->fileName();
    }

    // Returns the config file path
    static QString CC_CoreApps_ConfigFilePath() {
        return QString(CC_CoreApps_ConfigDir() + "/" + CC_CoreApps_ConfigFile());
    }

    // Returns the application dir
    static QString CC_System_AppPath() {
        return "/usr/share/applications/";
    }

    // Returns the home trash folder path
    static QString CC_Home_TrashDir() {
        return QString(QDir::homePath() + "/.local/share/Trash");
    }

    // Returns the mime file
    static QString CC_CoreApps_MimeFile() {
        return "mimeapps.list";
    }

    // Returns the mime file path
    static QString CC_CoreApps_MimeFilePath() {
        return QString(CC_CoreApps_ConfigDir() + "/" + CC_CoreApps_MimeFile());
    }
};

enum AppsName {
    Nothing      = 0x0000,
    CoreFM       = 0x0001,
    CoreImage    = 0x0002,
    CorePad      = 0x0003,
    Bookmarks    = 0x0004,
    About        = 0x0005,
    Start        = 0x0006,
    CorePaint    = 0x0007, 
    CorePlayer   = 0x0008,
    Settings     = 0x0009,
    Help         = 0x0010,
    Dashboard    = 0x0011,
    Search       = 0x0012,
    CoreTime     = 0x0013,
    CorePDF      = 0x0014,
    CoreRenamer  = 0x0015,
    CoreTerminal = 0x0016
};

enum Category {
    FileManager  = 0x0000,
    TextEditor   = 0x0001,
    ImageViewer  = 0x0002,
    ImageEditor  = 0x0003,
    MediaPlayer  = 0x0004,
    PDFViewer    = 0x0005,
    Terminal     = 0x0006
};

enum SortOrder {
    Ascending    = 0x0000,
    Descending   = 0x0001
};

enum MessageType {
    Info         = 0x0000,
    Warning      = 0x0001,
    Tips         = 0x0002
};

enum FileFolderSetup {
    BookmarkFolder   = 0x0000,
    DriveMountFolder = 0x0001,
    TrashFolder      = 0x0002,
    MimeFile         = 0x0003
};

enum StyleTypeName {
    AboutStyle         = 0x0000,
    BookmarkItStyle    = 0x0001,
    BookmarksStyle     = 0x0002,
    CoreActionStyle    = 0x0003,
    CoreArchiverStyle  = 0x0004,
    CoreBoxStyle       = 0x0005,
    CoreFMStyle        = 0x0006,
    CoreImageStyle     = 0x0007,
    CorePadStyle       = 0x0008,
    CorePaintStyle     = 0x0009,
    CorePlayerStyle    = 0x0010,
    CoreRenamerStyle   = 0x0011,
    CoreShotStyle      = 0x0012,
    CoreTimeStyle      = 0x0013,
    DashBoardStyle     = 0x0014,
    DialogStyle        = 0x0015,
    HelpStyle          = 0x0016,
    PropertiesStyle    = 0x0017,
    SearchStyle        = 0x0018,
    SettingsStyle      = 0x0019,
    StartStyle         = 0x0020
};

}
#endif // CPRIME_H
