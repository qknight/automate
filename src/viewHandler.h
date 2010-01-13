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

#ifndef VIEWHANDLER__HH__
#define VIEWHANDLER__HH__

enum ViewType {
  TreeViewType,
  GraphicsViewType
};

#include <QList>
#include <QDebug>

#include "AbstractView.h"

class automate;

class viewHandler {
friend class automate;
  private:
    /*! a list of views */
    QList<AbstractView*> ViewList;
    /*! add a view */
    void addHandle(AbstractView*);
    /*! delete a view */
    void delHandle(AbstractView*);
  public:
    /*! used to found out what views operate on an automate */
    const QList<AbstractView*> getListOfViews();
    /*! ... */
    viewHandler();
    /*! ... */
    ~viewHandler();
};

#endif
