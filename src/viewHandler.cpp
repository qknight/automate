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


#include "viewHandler.h"

viewHandler::viewHandler() {
//   qDebug() << "viewHandler ctor";
}

viewHandler::~viewHandler() {
//   qDebug("~viewHandler() %i", getListOfViews().size());

  foreach(AbstractView* t, ViewList) {
    delete t;
  }
}

void viewHandler::addHandle(AbstractView* z) {
  ViewList.push_back(z);
}

void viewHandler::delHandle(AbstractView* z) {
  for (int i=0; i < ViewList.size(); ++i) {
      if (ViewList[i] == z) {
          delete ViewList[i];
          ViewList.removeAt(i);
      }
  }
}

const QList<AbstractView*> viewHandler::getListOfViews() {
  return ViewList;
}
