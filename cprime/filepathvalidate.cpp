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

#include "filepathvalidate.h"

#include <QLineEdit>
#include <QDebug>
#include <QFileInfo>
#include <QPalette>

CPrime::FilePathValidate::FilePathValidate( QLineEdit *lineEdit, QObject *parent )
    : QObject ( parent )
{
    if ( !lineEdit ) {
        qDebug() << "Error 'nullptr': func(FilePathValidate) : LineEdit is null.";
        return;
    }

    mLineEdit = lineEdit;

    if ( !mLineEdit ) {
        qDebug() << "Error : Allocation problem.";
    }

    p = new QPalette( lineEdit->palette() );

    connect( mLineEdit, &QLineEdit::textChanged, this, &FilePathValidate::checkPathExistence );
}

void CPrime::FilePathValidate::addForValidation( QLineEdit *lineEdit, QObject *parent )
{
    new FilePathValidate( lineEdit, parent );
}

void CPrime::FilePathValidate::checkPathExistence( const QString &str )
{
    if ( str.count() ) {
        QFileInfo fi( str );
        QPalette *pal = new QPalette;
        pal->setColor( QPalette::Text, Qt::red );

        if ( fi.exists() ) {
            mLineEdit->setPalette( *p );
        } else {
            mLineEdit->setPalette( *pal );
        }
    } else {
        mLineEdit->setPalette( *p );
        //mLineEdit->setPlaceholderText( "Enter valid path..." );
    }
}
