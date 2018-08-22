QT       += widgets core

TARGET = cprime
TEMPLATE = lib

# disable all build warnings
CONFIG += silent warn_on static

DEFINES += LIBCPRIME_LIBRARY

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
        includes.files	                = cprime/*.h libcprime_global.h
        includes.path		        = $$PREFIX/include/cprime/

        data.path = $$PREFIX/share/lib$$TARGET/
        data.files = Changelog README

        QMAKE_PKGCONFIG_NAME = libcprime
        QMAKE_PKGCONFIG_DESCRIPTION = Library for coreapps
        QMAKE_PKGCONFIG_PREFIX  = $$INSTALL_PREFIX
        QMAKE_PKGCONFIG_LIBDIR  = $$target.path
        QMAKE_PKGCONFIG_INCDIR  = $$includes.path
        QMAKE_PKGCONFIG_VERSION = $$VERSION
        QMAKE_PKGCONFIG_DESTDIR = pkgconfig
}

HEADERS += \
    cprime/globalfunctions.h \
    cprime/utilities.h \
    cprime/settingsmanage.h \
    cprime/bookmarkmanage.h \
    libcprime_global.h

SOURCES += \
    cprime/globalfunctions.cpp \
    cprime/utilities.cpp \
    cprime/settingsmanage.cpp \
    cprime/bookmarkmanage.cpp

RESOURCES += \
    style.qrc \
