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

#include <QTimer>
#include <QFileInfo>

#include "cprime.h"

#include "bookmarkmanage.h"
#include "bookmarkdialog.h"
#include "ui_bookmarkdialog.h"

bookmarkDialog::bookmarkDialog( QWidget *parent ) : QDialog( parent ), ui( new Ui::bookmarkDialog )
{
    ui->setupUi( this );

    // set stylesheet from style.qrc
    setStyleSheet( CPrime::ThemeFunc::getStyleSheetFileContent( CPrime::StyleTypeName::DialogStyle ) );

    // set the requried folders
    CPrime::ValidityFunc::setupFileFolder( CPrime::FileFolderSetup::BookmarkFolder );

    connect( ui->cancel, &QToolButton::clicked, this, &bookmarkDialog::close );

    ui->bkSection->clear();
    ui->bkSection->addItems( bk.getBookSections() );
    ui->done->setEnabled( false );

    BookmarkManage bm;
    bm.checkBook();
}

bookmarkDialog::~bookmarkDialog()
{
    delete ui;
}

void bookmarkDialog::on_done_clicked()
{
    if ( ui->bkName->text().count() == 0 ) {
        ui->done->setEnabled( false );
    }

    if ( ui->bkName->text().count() != 0 && ui->bkSection->currentText().count() != 0 ) {
        accepted = true;
        QTimer::singleShot( 100, this, SLOT( close() ) );
        // Function from utilities.cpp
        CPrime::InfoFunc::messageEngine( "Bookmark Added at '" + ui->bkSection->currentText() + "'", CPrime::MessageType::Info, this );
    }
}

void bookmarkDialog::bookMarkName_Changed()
{
    if ( ui->bkName->text().count() > 0 ) {
        QString str = bk.checkingBookName( ui->bkSection->currentText(), ui->bkName->text() );

        if ( str.count() > 0 ) {
            ui->bkStatus->setText( str );
            ui->done->setEnabled( false );
        } else {
            ui->bkStatus->setText( str );
            ui->done->setEnabled( true );
        }
    } else {
        ui->done->setEnabled( false );
    }
}

void bookmarkDialog::checkPath()
{
    QString str = bk.checkingBookPath( ui->bkSection->currentText(), ui->bkName->text() );

    if ( str.count() > 0 ) {
        ui->bkStatus->setText( str );
        ui->bkName->setEnabled( false );
        ui->done->setEnabled( false );
        ui->cancel->setText( "OK" );
    } else {
        ui->bkStatus->setText( str );
        ui->bkName->setEnabled( true );
        ui->done->setEnabled( true );
        ui->cancel->setText( "Cancel" );
    }
}

void bookmarkDialog::setBookPath( const QString &path )
{
    ui->path->setText( path );
}

void bookmarkDialog::setBookName( const QString &bName )
{
    ui->bkName->setText( bName );
}

QString bookmarkDialog::getBookName()
{
    return ui->bkName->text();
}

QString bookmarkDialog::getSectionName()
{
    return ui->bkSection->currentText();
}

void bookmarkDialog::item_Changed()
{
    checkPath();
    bookMarkName_Changed();
}


void bookmarkDialog::on_bkSection_currentIndexChanged( const QString &arg1 )
{
    Q_UNUSED( arg1 );
    checkPath();
    bookMarkName_Changed();
}

void bookmarkDialog::on_bkName_textChanged( const QString &arg1 )
{
    Q_UNUSED( arg1 );

    if ( ui->bkName->text().count() > 0 ) {
        QString str = bk.checkingBookName( ui->bkSection->currentText(), ui->bkName->text() );

        if ( str.count() > 0 ) {
            ui->bkStatus->setText( str );
            ui->done->setEnabled( false );
        } else {
            ui->bkStatus->setText( str );
            ui->done->setEnabled( true );
        }
    } else {
        ui->done->setEnabled( false );
    }
}

/**
 * @brief Call add bookmark dialog from any apps by giving the path to book it.
 * @brief And also the apps icon.
 * @param currentPath : Path which needs to bookmarked.
 * @param iconPath : Apps icon path from resource.
 */
void bookmarkDialog::callBookMarkDialog( QWidget *parent, const QString &currentPath )
{
    QFileInfo info( currentPath );
    BookmarkManage bm;
    const QString str = bm.checkingBookPathEx( currentPath );

    if ( str.count() == 0 ) {
        bookmarkDialog *bkdlg = new bookmarkDialog( parent );
        QIcon ico = CPrime::ThemeFunc::getFileIcon( currentPath );
        QPixmap pix = ico.pixmap( QSize( 100, 80 ) );
        bkdlg->setBookPath( currentPath );
        bkdlg->setBookName( info.fileName() + "" );
        bkdlg->checkPath();

        if ( bkdlg->exec() == 0 ) {
            if ( bkdlg->accepted ) {
                bk.addBookmark( bkdlg->getSectionName(), bkdlg->getBookName(), currentPath );
            } else if ( !bkdlg->accepted ) {
                bkdlg->close();
            }
        }

        //sectionRefresh();
    } else {
        // Function from utilities.cpp
        CPrime::InfoFunc::messageEngine( str, CPrime::MessageType::Info, this );
    }
}
