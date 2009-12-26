// automate implements an automate class in c++ using qt4
// Copyright (C) 2007 Joachim Schiele
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// version 3 as published by the Free Software Foundation
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

#ifndef OBJECTPROPERTY_H
#define OBJECTPROPERTY_H

#include <QHash>
#include <QVariant>
#include <QDebug>

/*! this class does what a QObject deriving class also does but this is the lightweight solution */
class objectProperty {
  public:
    /*! constructor */
    objectProperty();
    /*! destuctor */
    ~objectProperty();
    /*! get a property, init it with  */
    const QVariant getProperty( QString key, QVariant init );
    /*! set a property */
    void setProperty( QString, QVariant );
  public:
    /*! get a property */
    const QVariant getProperty( QString );

  private: // Members
    /*! holds all properties */
    QHash<QString, QVariant> property;
};

#endif
