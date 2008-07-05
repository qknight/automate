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

#ifndef AUTOMATECORE__HH__
#define AUTOMATECORE__HH__

#include <QDate>

#include "AutomateRoot.h"
#include "AbstractTreeItem.h"
#include "AbstractView.h"
#include "viewHandler.h"
#include "mainGraphicsView.h"
#include "treeView.h"
#include "Model.h"
#include "modeltest/modeltest.h"


class automate {
  private:
    AutomateRoot* root;
    Model* modelPtr;

  public:
    automate();
    ~automate();
    viewHandler* vh;
    Model* model();
    void openNewView(ViewType);
    void dump();
    unsigned int childCount();
    unsigned int connectionCount();

  //TODO make private later and or remove it
    AbstractTreeItem* automateRootPtr();
    QString name;
  private:
    ModelTest* modeltest;
};

#endif
