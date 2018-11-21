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

#ifndef SETTINGSMANAGE_H
#define SETTINGSMANAGE_H

#include "libcprime_global.h"

class QSettings;
class QVariant;

class LIBCPRIMESHARED_EXPORT SettingsManage {

public:
    SettingsManage();
    QSettings *cSetting;
    void createDefaultSettings();

    bool setSpecificValue( QString groupName, QString keyName, QVariant value );
    QVariant getSpecificValue( QString groupName, QString keyName ) const;

    QString getTerminal() const;
    bool setTerminal( const QString &termName );

    QString getStartupPath() const;
    bool setStartupPath( const QString &path );

    QString getThemeName() const;
    bool setThemeName( const QString &themeName );

    bool setFileManager( const QString &fmName );
    QString getFileManager() const;

    bool setTextEditor( const QString &textEditorName );
    QString getTextEditor() const;

    bool setImageViewer( const QString &imageViewerName );
    QString getImageViewer() const;

    bool setImageEditor( const QString &imageEditorName );
    QString getImageEditor() const;

    bool setPDFVierwer( const QString &imageEditorName );
    QString getPDFVierwer() const;

    bool setMediaPlayer( const QString &imageEditorName );
    QString getMediaPlayer() const;

    bool getIsRealMimeType() const;
    bool setIsRealMimeType( bool isRealMime );

    int getZoomValue() const;
    bool setZoomValue( const int &value );

    int getZoomTreeValue() const;
    bool setZoomTreeValue( const int &value );

    int getZoomListValue() const;
    bool setZoomListValue( const int &value );

    int getZoomDetailValue() const;
    bool setZoomDetailValue( const int &value );

    bool getIsShowThumb() const;
    bool setIsShowThumb( bool isShowThumb );

    bool getShowToolbox() const;
    bool setShowToolbox( bool showTool );

    bool getViewMode() const;
    bool setViewMode( bool mode );

    QString getSCSaveLocation() const;
    bool setSCSaveLocation( const QString &path );

    bool getShowBattery() const;
    bool setSHowBattery( bool showBattery );

    bool getShowRecent() const;
    bool setShowRecent( bool showRecent );

    QString getTimeFormat() const;
    bool setTimeFormat( const QString &AmPm );

    bool getShowHidden() const;
    bool setShowHidden( bool showTool );

    bool getShowCalander() const;
    bool setSHowCalander( bool showBattery );

    bool getShowSystem() const;
    bool setSHowSystem( bool showSystem );

    bool getShowNetwork() const;
    bool setSHowNetwork( bool showNetwork );

    bool getShowCalculator() const;
    bool setSHowCalculator( bool showCalculator );

    bool getShowNote() const;
    bool setSHowNote( bool showNote );

    bool setSHowTime( bool showTime );
    bool getShowTime() const;

    bool setStyleMode( bool mode );
    bool getStyleMode() const;

    bool setFontStyle( const QString &fontStyle );
    QString getFontStyle() const;

    bool setAddShadow( bool addShadow );
    bool getAddShadow() const;
};

#endif // SETTINGSMANAGE_H
