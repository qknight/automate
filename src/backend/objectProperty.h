/*
    This file is part of automate.
      Copyright Joachim Schiele
      
    automate is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License.

    automate is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with automate.  If not, see <http://www.gnu.org/licenses/>.
*/

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
