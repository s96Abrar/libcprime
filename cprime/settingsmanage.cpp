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

#include "settingsmanage.h"


SettingsManage::SettingsManage()
{
    cSetting = new QSettings("coreBox", "coreBox");
}

void SettingsManage::createDefaultSettings()
{
    if (!QFileInfo(cSetting->fileName()).exists())
    {
        cSetting->beginGroup("CoreApps");
        cSetting->setValue("Recent-Disable", false);
        cSetting->setValue("Force-Theme", QIcon::themeName());
        cSetting->setValue("Style-Mode", false);
        cSetting->setValue("Font-Style", "Cantarell");
        cSetting->setValue("Add-Shadow", true);
        cSetting->setValue("Terminal", "CoreTerminal");
        cSetting->setValue("File-Manager", "CoreFM");
        cSetting->setValue("Text-Editor", "CorePad");
        cSetting->setValue("Image-Viewer", "CoreImage");
        cSetting->setValue("Image-Editor", "CorePaint");
        cSetting->setValue("Media-Player", "CorePlayer");
        cSetting->setValue("PDF-Viewer", "CorePDF");
        cSetting->endGroup();

        cSetting->beginGroup("CoreFM");
        cSetting->setValue("Startup-Path", QDir::homePath());
        cSetting->setValue("Real-Mime-Types", true);
        cSetting->setValue("Zoom", 32);
        cSetting->setValue("Zoom-Tree", 16);
        cSetting->setValue("Zoom-List", 32);
        cSetting->setValue("Zoom-Detail", 24);
        cSetting->setValue("Show-Thumb", false);
        cSetting->setValue("Show-Toolbox", false);
        cSetting->setValue("Show-Hidden",false);
        cSetting->setValue("View-Mode", true);
        cSetting->endGroup();

        cSetting->beginGroup("CoreScreenshot");
        cSetting->setValue("Save-Location", QDir::homePath() + "/Pictures");
        cSetting->endGroup();

        cSetting->beginGroup("CoreAction");
        cSetting->setValue("Show-Time", true);
        cSetting->setValue("Show-Battery", false);
        cSetting->setValue("Show-System", false);
        cSetting->setValue("Show-Network", false);
        cSetting->setValue("Show-Calander", false);
        cSetting->setValue("Show-Calculator", true);
        cSetting->setValue("Show-Note", true);
        cSetting->endGroup();
    }
}

bool SettingsManage::setSpecificValue(QString groupName, QString keyName, QVariant value) {
    if (!groupName.isEmpty() && !keyName.isEmpty()) {
        cSetting->beginGroup(groupName);
        cSetting->setValue(keyName, value);
        cSetting->endGroup();
        return true;
    }
    return false;
}

QVariant SettingsManage::getSpecificValue(QString groupName, QString keyName) const {
    if (!groupName.isEmpty() && !keyName.isEmpty()) {
        cSetting->beginGroup(groupName);
        QVariant v = cSetting->value(keyName);
        cSetting->endGroup();
        return v;
    }
    return QVariant();
}

//-------------------------CoreApps--------------------------------------

bool SettingsManage::setThemeName(const QString &themeName) {
    return setSpecificValue("CoreApps", "Force-Theme", themeName);
}

QString SettingsManage::getThemeName() const {
    return getSpecificValue("CoreApps", "Force-Theme").toString();
}

bool SettingsManage::setShowRecent(bool showRecent) {
    return setSpecificValue("CoreApps", "Recent-Disable", showRecent);
}

bool SettingsManage::getShowRecent() const {
    return getSpecificValue("CoreApps", "Recent-Disable").toBool();
}

bool SettingsManage::setStyleMode(bool mode) {
    return setSpecificValue("CoreApps", "Style-Mode", mode);
}

bool SettingsManage::getStyleMode() const {
    return getSpecificValue("CoreApps", "Style-Mode").toBool();
}

bool SettingsManage::setFontStyle(const QString &fontStyle) {
    return setSpecificValue("CoreApps", "Font-Style", fontStyle);
}

QString SettingsManage::getFontStyle() const {
    return getSpecificValue("CoreApps", "Font-Style").toString();
}

bool SettingsManage::setAddShadow(bool addShadow) {
    return setSpecificValue("CoreApps", "Add-Shadow", addShadow);
}

bool SettingsManage::getAddShadow() const {
    return getSpecificValue("CoreApps", "Add-Shadow").toBool();
}

bool SettingsManage::setTerminal(const QString &termName) {
    return setSpecificValue("CoreApps", "Terminal", termName);
}

QString SettingsManage::getTerminal() const{
    return getSpecificValue("CoreApps", "Terminal").toString();
}

bool SettingsManage::setFileManager(const QString &fmName) {
    return setSpecificValue("CoreApps", "File-Manager", fmName);
}

QString SettingsManage::getFileManager() const {
    return getSpecificValue("CoreApps", "File-Manager").toString();
}

bool SettingsManage::setTextEditor(const QString &textEditorName) {
    return setSpecificValue("CoreApps", "Text-Editor", textEditorName);
}

QString SettingsManage::getTextEditor() const {
    return getSpecificValue("CoreApps", "Text-Editor").toString();
}

bool SettingsManage::setImageViewer(const QString &imageViewerName) {
    return setSpecificValue("CoreApps", "Image-Viewer", imageViewerName);
}

QString SettingsManage::getImageViewer() const {
    return getSpecificValue("CoreApps", "Image-Viewer").toString();
}

bool SettingsManage::setImageEditor(const QString &imageEditorName) {
    return setSpecificValue("CoreApps", "Image-Editor", imageEditorName);
}

QString SettingsManage::getImageEditor() const {
    return getSpecificValue("CoreApps", "Image-Editor").toString();
}

bool SettingsManage::setPDFVierwer(const QString &pdfVierwerName) {
    return setSpecificValue("CoreApps", "PDF-Viewer", pdfVierwerName);
}

QString SettingsManage::getPDFVierwer() const {
    return getSpecificValue("CoreApps", "PDF-Viewer").toString();
}

bool SettingsManage::setMediaPlayer(const QString &imageEditorName) {
    return setSpecificValue("CoreApps", "Media-Player", imageEditorName);
}

QString SettingsManage::getMediaPlayer() const {
    return getSpecificValue("CoreApps", "Media-Player").toString();
}
//-------------------------CoreApps--------------------------------------


//-------------------------CoreFM--------------------------------------

bool SettingsManage::setStartupPath(const QString &path) {
    return setSpecificValue("CoreFM", "Startup-Path", path);
}

QString SettingsManage::getStartupPath() const{
    return getSpecificValue("CoreFM", "Startup-Path").toString();
}

bool SettingsManage::setIsRealMimeType(bool isRealMime) {
    return setSpecificValue("CoreFM", "Real-Mime-Types", isRealMime);
}

bool SettingsManage::getIsRealMimeType() const {
    return getSpecificValue("CoreFM", "Real-Mime-Types").toBool();
}

bool SettingsManage::setZoomValue(const int &value) {
    return setSpecificValue("CoreFM", "Zoom", value);
}

int SettingsManage::getZoomValue() const {
    return getSpecificValue("CoreFM", "Zoom").toInt();
}

bool SettingsManage::setZoomTreeValue(const int &value) {
    return setSpecificValue("CoreFM", "Zoom-Tree", value);
}

int SettingsManage::getZoomTreeValue() const{
    return getSpecificValue("CoreFM", "Zoom-Tree").toInt();
}

bool SettingsManage::setZoomListValue(const int &value) {
    return setSpecificValue("CoreFM", "Zoom-List", value);
}

int SettingsManage::getZoomListValue() const {
    return getSpecificValue("CoreFM", "Zoom-List").toInt();
}

bool SettingsManage::setZoomDetailValue(const int &value) {
    return setSpecificValue("CoreFM", "Zoom-Detail", value);
}

int SettingsManage::getZoomDetailValue() const {
    return getSpecificValue("CoreFM", "Zoom-Detail").toInt();
}

bool SettingsManage::setIsShowThumb(bool isShowThumb) {
    return setSpecificValue("CoreFM", "Show-Thumb", isShowThumb);
}

bool SettingsManage::getIsShowThumb() const {
    return getSpecificValue("CoreFM", "Show-Thumb").toBool();
}

bool SettingsManage::setShowToolbox(bool showTool) {
    return setSpecificValue("CoreFM", "Show-Toolbox", showTool);
}

bool SettingsManage::getShowToolbox() const {
    return getSpecificValue("CoreFM", "Show-Toolbox").toBool();
}

bool SettingsManage::setShowHidden(bool showTool) {
    return setSpecificValue("CoreFM", "Show-Hidden", showTool);
}

bool SettingsManage::getShowHidden() const {
    return getSpecificValue("CoreFM", "Show-Hidden").toBool();
}

bool SettingsManage::setViewMode(bool mode) {
    return setSpecificValue("CoreFM", "View-Mode", mode);
}

bool SettingsManage::getViewMode() const {
    return getSpecificValue("CoreFM", "View-Mode").toBool();
}

//-------------------------CoreFM--------------------------------------

//-------------------------CoreScreenshot------------------------------

bool SettingsManage::setSCSaveLocation(const QString &path) {
    return setSpecificValue("CoreScreenshot", "Save-Location", path);
}

QString SettingsManage::getSCSaveLocation() const {
    return getSpecificValue("CoreScreenshot", "Save-Location").toString();
}

//-------------------------CoreScreenshot------------------------------

//-------------------------CoreAction------------------------------

bool SettingsManage::setSHowTime(bool showTime) {
    return setSpecificValue("CoreAction", "Show-Time", showTime);
}

bool SettingsManage::getShowTime() const {
    return getSpecificValue("CoreAction", "Show-Time").toBool();
}

bool SettingsManage::setSHowBattery(bool showBattery) {
    return setSpecificValue("CoreAction", "Show-Battery", showBattery);
}

bool SettingsManage::getShowBattery() const {
    return getSpecificValue("CoreAction", "Show-Battery").toBool();
}

bool SettingsManage::setSHowSystem(bool showSystem) {
    return setSpecificValue("CoreAction", "Show-System", showSystem);
}

bool SettingsManage::getShowSystem() const {
    return getSpecificValue("CoreAction", "Show-System").toBool();
}

bool SettingsManage::setSHowNetwork(bool showNetwork) {
    return setSpecificValue("CoreAction", "Show-Network", showNetwork);
}

bool SettingsManage::getShowNetwork() const {
    return getSpecificValue("CoreAction", "Show-Network").toBool();
}

bool SettingsManage::setSHowCalander(bool showCalander) {
    return setSpecificValue("CoreAction", "Show-Calander", showCalander);
}

bool SettingsManage::getShowCalander() const {
    return getSpecificValue("CoreAction", "Show-Calander").toBool();
}

bool SettingsManage::setSHowCalculator(bool showCalculator) {
    return setSpecificValue("CoreAction", "Show-Calculator", showCalculator);
}

bool SettingsManage::getShowCalculator() const {
    return getSpecificValue("CoreAction", "Show-Calculator").toBool();
}

bool SettingsManage::setSHowNote(bool showNote) {
    return setSpecificValue("CoreAction", "Show-Note", showNote);
}

bool SettingsManage::getShowNote() const {
    return getSpecificValue("CoreAction", "Show-Note").toBool();
}

//-------------------------CoreAction------------------------------
