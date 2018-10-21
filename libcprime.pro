QT       += widgets core gui

TARGET    = cprime
TEMPLATE  = lib

# disable all build warnings
CONFIG   += silent warn_on thread silent build_all c++11

INCLUDEPATH += ./cprime/
DEPENDPATH  += ./cprime/

# Disable Debug on Release
#CONFIG(release):DEFINES += QT_NO_DEBUG_OUTPUT

VERSION  = 2.3.0
DEFINES  += LIBCPRIME_LIBRARY

HEADERS += \
    cprime/globalfunctions.h \
    cprime/utilities.h \
    cprime/settingsmanage.h \
    cprime/bookmarkmanage.h \
    cprime/bookmarkdialog.h \
    cprime/applicationdialog.h \
    cprime/desktopfile.h \
    cprime/properties.h \
    libcprime_global.h \
    cprime/mimeutils.h \
    cprime/stringfunc.h

SOURCES += \
    cprime/globalfunctions.cpp \
    cprime/utilities.cpp \
    cprime/settingsmanage.cpp \
    cprime/bookmarkmanage.cpp \
    cprime/bookmarkdialog.cpp \
    cprime/applicationdialog.cpp \
    cprime/desktopfile.cpp \
    cprime/properties.cpp \
    cprime/mimeutils.cpp \
    cprime/stringfunc.cpp

FORMS += \
    cprime/bookmarkdialog.ui


MOC_DIR			= ../build/moc
OBJECTS_DIR		= ../build/obj
RCC_DIR			= ../build/qrc
UI_DIR			= ../build/uic

# Must needed
RESOURCE_FOLDER = /usr/share/coreapps
THEME_FOLDER    = $$RESOURCE_FOLDER/theme
DEFINES += COREAPPS_THEME_FOLDER=\"\\\"$${THEME_FOLDER}\\\"\"

unix {
        isEmpty(PREFIX) {
                PREFIX = /usr
        }

        INSTALLS	 += target includes data themefiles
        CONFIG		 += create_pc no_install_prl link_pkgconfig
        contains(DEFINES, LIB64): target.path = $$INSTALL_PREFIX/lib64
        else: target.path = $$INSTALL_PREFIX/lib

        target.path	  = $$PREFIX/lib/

        includes.files    = cprime/*.h libcprime_global.h
        includes.path     = $$PREFIX/include/cprime/

        data.path         = $$PREFIX/share/coreapps/docs
        data.files        = docs/Changelog docs/LICENSE docs/To-Do.txt docs/ReleaseNotes

<<<<<<< HEAD
        themefiles.path   = /usr/share/coreapps/theme
        themefiles.files  = style/*.qss style/*.ini
=======
        themefiles.path   = $$PREFIX/share/coreapps/theme
        themefiles.files  = theme/*.qss theme/*.ini
>>>>>>> a14ed78b4d9c66220fcab55eb9b4cc6bf4f496f6

        QMAKE_PKGCONFIG_NAME        = libcprime
        QMAKE_PKGCONFIG_DESCRIPTION = Library for coreapps
        QMAKE_PKGCONFIG_PREFIX      = $$INSTALL_PREFIX
        QMAKE_PKGCONFIG_LIBDIR      = $$target.path
        QMAKE_PKGCONFIG_INCDIR      = $$includes.path
        QMAKE_PKGCONFIG_VERSION     = $$VERSION
        QMAKE_PKGCONFIG_DESTDIR     = pkgconfig
}
<<<<<<< HEAD

HEADERS += \
    cprime/globalfunctions.h \
    cprime/utilities.h \
    cprime/settingsmanage.h \
    cprime/bookmarkmanage.h \
    cprime/bookmarkdialog.h \
    cprime/applicationdialog.h \
    cprime/desktopfile.h \
    cprime/properties.h \
    libcprime_global.h \
    cprime/mimeutils.h \
    cprime/stringfunc.h \
    cprime/cprime.h \
    cprime/themefunc.h \
    cprime/sortfunc.h \
    cprime/validityfunc.h \
    cprime/appopenfunc.h \
    cprime/infofunc.h \
    cprime/filefunc.h \
    cprime/trashmanager.h

SOURCES += \
    cprime/globalfunctions.cpp \
    cprime/utilities.cpp \
    cprime/settingsmanage.cpp \
    cprime/bookmarkmanage.cpp \
    cprime/bookmarkdialog.cpp \
    cprime/applicationdialog.cpp \
    cprime/desktopfile.cpp \
    cprime/properties.cpp \
    cprime/mimeutils.cpp \
    cprime/stringfunc.cpp \
    cprime/themefunc.cpp \
    cprime/sortfunc.cpp \
    cprime/validityfunc.cpp \
    cprime/appopenfunc.cpp \
    cprime/infofunc.cpp \
    cprime/filefunc.cpp \
    cprime/trashmanager.cpp
    
FORMS += \
    cprime/bookmarkdialog.ui
=======
>>>>>>> a14ed78b4d9c66220fcab55eb9b4cc6bf4f496f6
    
