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

#ifndef THEMEFUNC_H
#define THEMEFUNC_H

#include <QIODevice>

#include "cenums.h"
#include "libcprime_global.h"

class QWidget;
class QSettings;

namespace CPrime {

    class LIBCPRIMESHARED_EXPORT ThemeFunc {
    public:
        static void addDropShadow( QWidget *widget, const int alpha, const QColor color, const int blur = 25, const QString &styleSheet = "" );
        static void addDropShadow( QWidget *widget, const int alpha, const int blur = 25, const QString &styleSheet = "" );
        static QIcon getAppIcon( const QString &appName );
        static QIcon getFileIcon( const QString &filePath );
        static QSettings *getStyleSheet();
        static QString getStyleSheetFileContent( CPrime::StyleTypeName s );
        static QString readStringFromFile( const QString &path, QIODevice::OpenMode mode );
    };

}

#endif // THEMEFUNC_H
