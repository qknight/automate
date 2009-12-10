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
