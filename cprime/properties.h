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

#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QStringList>
#include <QVariant>
#include <QObject>
#include <QMap>

#include "libcprime_global.h"

/**
 * @class Properties
 * @brief Read property files
 * @author Michal Rost
 * @date 26.1.2013
 */
class LIBCPRIMESHARED_EXPORT Properties {

public:
  explicit Properties(const QString &fileName = "", const QString &group = "");
  explicit Properties(const Properties &other);
  QVariant value(const QString &key, const QVariant &defaultValue = QVariant());
  bool load(const QString &fileName, const QString &group = "");
  bool save(const QString &fileName, const QString &group = "");
  void set(const QString &key, const QVariant &value);
  bool contains(const QString &key) const;
  QStringList getKeys() const;

protected:
  QMap<QString, QVariant> data;

};

#endif // PROPERTIES_H
