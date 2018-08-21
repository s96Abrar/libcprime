QT       += widgets core

TARGET = cprime
TEMPLATE = lib

# disable all build warnings
CONFIG += silent warn_on shared_and_static


# Disable Debug on Release
CONFIG(release):DEFINES += QT_NO_DEBUG_OUTPUT

VERSION = 1.0.9
DEFINES += LIBCPRIME_LIBRARY



MOC_DIR			= ../build/moc
OBJECTS_DIR		= ../build/obj
RCC_DIR			= ../build/qrc
UI_DIR			= ../build/uic

unix {
        isEmpty(PREFIX) {
                PREFIX = /usr
        }

        INSTALLS	+= target includes data
        CONFIG		+= create_pc no_install_prl link_pkgconfig
        contains(DEFINES, LIB64): target.path = $$INSTALL_PREFIX/lib64
        else: target.path = $$INSTALL_PREFIX/lib

        target.path			= $$PREFIX/lib/
        includes.files	=  globalfunctions.h utilities.h settingsmanage.h bookmarkmanage.h
        includes.path		= $$PREFIX/include/

        data.path = $$PREFIX/share/lib$$TARGET/
        data.files = Changelog README

        QMAKE_PKGCONFIG_NAME = libcprime
        QMAKE_PKGCONFIG_DESCRIPTION = A Qt based archiving solution with libarchive backend
        QMAKE_PKGCONFIG_PREFIX  = $$INSTALL_PREFIX
        QMAKE_PKGCONFIG_LIBDIR  = $$target.path
        QMAKE_PKGCONFIG_INCDIR  = $$includes.path
        QMAKE_PKGCONFIG_VERSION = $$VERSION
        QMAKE_PKGCONFIG_DESTDIR = pkgconfig
}

HEADERS += \
    globalfunctions.h \
    utilities.h \
    settingsmanage.h \
    bookmarkmanage.h

SOURCES += \
    globalfunctions.cpp \
    utilities.cpp \
    settingsmanage.cpp \
    bookmarkmanage.cpp

RESOURCES += \
    style.qrc \
    icons.qrc
