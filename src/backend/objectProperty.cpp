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
//   if (!property.contains(key)) {
//     qDebug() << __FILE__ << " " << __FUNCTION__ << " ERROR: getProperty for key " << key << " not found in property space";
//     qDebug() << __FILE__ << " " << __FUNCTION__ << " FIX your code, and try again, exiting now";
//     exit(1);
//   }
  return property.value(key);
}
