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

#include <QChar>
#include <QFont>
#include <QFontMetrics>

#include "stringfunc.h"

QString CPrime::StringFunc::CapitalizeEachWord( const QString &str )
{
    if ( str.count() == 0 ) {
        qDebug() << "Error : func(CapitalizeEachWord) : Empty String.";
        return nullptr;
    }

    QStringList sep = str.split( ' ' );
    QString total = nullptr;

    foreach ( QString s, sep ) {
        if ( !s.count() ) {
            continue;
        }

        foreach ( QChar c, s ) {
            if ( c.isLetter() ) {
                s = s.toLower().replace( s.indexOf( c ), 1, c.toTitleCase() );
                break;
            }
        }

        total = total + " " + s;
    }

    if ( !total.count() ) {
        qDebug() << "Error : func(CapitalizeEachWord) : Nothing to return.";
        return nullptr;
    }

    return total.remove( 0, 1 );
}

QStringList CPrime::StringFunc::fStringList( QStringList &left, QStringList &right, QFont font )
{
    if ( !left.count() || !right.count() ) {
        qDebug() << "Error : func(fStringList) : Empty list given.";
        return ( QStringList() << nullptr );
    }

    QFontMetrics *fontM = new QFontMetrics( font );
    int large = 0;

    foreach ( QString s, left ) {
        if ( large < fontM->width( s ) ) {
            large = fontM->width( s );
        }
    }

    large = large + fontM->width( '\t' );

    int index = 0;

    for ( index = 0; index < left.count(); index++ ) {
        while ( large >= fontM->width( left.at( index ) ) ) {
            left.replace( index, QString( left.at( index ) + QString( '\t' ) ) );
        }
    }

    index = 0;

    foreach ( QString s, left ) {
        QString rFirstW = s.at( 0 ).toUpper();
        QString rRestW  = s.right( s.length() - 1 );
        left.replace( index, rFirstW + rRestW + ": " + right.at( index ) );
        index++;
    }

    return left;
}
