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

#include "objectProperty.h"

objectProperty::objectProperty() { }

objectProperty::~objectProperty() { }

void objectProperty::setProperty(QString key, QVariant value) {
  property.insert(key,value);
}

// this is a convenience function, to stop program termination on faults
const QVariant objectProperty::getProperty(QString key, QVariant init) {
  if (!property.contains(key)) {
    property.insert(key,init);
  }
  return property.value(key);
}

const QVariant objectProperty::getProperty(QString key) {
  if (!property.contains(key)) {
    qDebug() << "ERROR: getProperty for key " << key << " not found in property space";
    qDebug() << "FIX your code, and try again, exiting now";
    exit(1);
  }
  return property.value(key);
}
