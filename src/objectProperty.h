// automate implements an automate class in c++ using qt4
// Copyright (C) 2007 Joachim Schiele
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// version 2 as published by the Free Software Foundation
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

/**
  @author Joachim Schiele <js@lastlog.de>
*/

// this code does basically the same as QT4 qobject code already does
// it's always nice to reinvent the wheel and reduce readability in code
// -> will be changed later to qt4 way of doing

#ifndef OBJECTPROPERTY_H
#define OBJECTPROPERTY_H

#include <QHash>
#include <QVariant>
#include <QDebug>

/**
	@author Joachim Schiele <js@lastlog.de>
*/

class objectProperty{
public://protected:
  objectProperty();
  ~objectProperty();
  const QVariant getProperty(QString, QVariant );
  void setProperty(QString, QVariant);
public:
  const QVariant getProperty(QString);
  // QVector<QString> getAllProperties();

private: // Members
  QHash<QString, QVariant> property;
};

#endif
