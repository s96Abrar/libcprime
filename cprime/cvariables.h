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

#ifndef CVARIABLES_H
#define CVARIABLES_H

#include "libcprime_global.h"

namespace CPrime {

    class LIBCPRIMESHARED_EXPORT Variables {
    public:
        // Returns the file path where docs located.
        static QString CC_CoreApps_DataDir() {
            return "/usr/share/coreapps/docs/";
        }

        // Returns the release note file path
        static QString CC_CoreApps_ReleaseNoteFilePath() {
            return QString( CC_CoreApps_DataDir() + "ReleaseNotes" );
        }

        // Returns the Configuration folder path
        static QString CC_CoreApps_ConfigDir();

        // Returns the temporary mount folder path
        static QString CC_CoreApps_MountDir();

        // Returns the Bookmark file name
        static QString CC_CoreApps_BookMarkFile() {
            return "CoreBoxBook";
        }

        // Returns the Bookmark file path
        static QString CC_CoreApps_BookMarkFilePath();

        // Returns the config file
        static QString CC_CoreApps_ConfigFile();

        // Returns the config file path
        static QString CC_CoreApps_ConfigFilePath();

        // Returns the application dir
        static QString CC_System_AppPath() {
            return "/usr/share/applications/";
        }

        // Returns the home trash folder path
        static QString CC_Home_TrashDir();

        // Returns the mime file
        static QString CC_CoreApps_MimeFile() {
            return "mimeapps.list";
        }

        // Returns the mime file path
        static QString CC_CoreApps_MimeFilePath();

        // Returns the Recent activity file
        static QString CC_CoreApps_RecentActFile() {
            return "RecentActivity";
        }

        // Returns the Recent activity file path
        static QString CC_CoreApps_RecentActFilePath();
    };

}

#endif // CVARIABLES_H
