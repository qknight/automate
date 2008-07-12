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
#include "graphicsView.h"
#include "treeView.h"
#include "Model.h"

// #define MODELTEST
#ifdef MODELTEST
#include "modeltest/modeltest.h"
#endif

/*!
** This class represents an automate (NFA/DFA/others) and encapsulates
** the data structure, a model, accommodates the views.
** If you want to debug the model this is the right place to do so.
*/
class automate {
  public:
    /*! Constructs a new automate which implicitly creates a model and a AutomateRoot */
    automate();
    /*! Destructs this automate which implicitly destries all views and their data,
    deletes the model and all data */
    ~automate();
    /*! The viewHandler handles all kind of views:
      - QTreeView (treeView)
      - QAbstractItemView (graphicsView), a custom view wrapped into a QGraphicsScene */
    viewHandler* vh;
    /*! Every automate has exactly one model which is used for modifications of the data. */
    Model* model();
    /*! As the name says, this function opens a new view for this automate. */
    void openNewView(ViewType);
    /*! This wrapper function is called by the gui and it will forward this call to the AutomateRoot
        which will recursively call this for all it's childs.*/
    void dump();
    /*! This wrapper function is called by the gui and it will forward this call to the AutomateRoot
        It returns the number of used nodes (not edges)*/
    unsigned int childCount();
    /*! This wrapper function is called by the gui and it will forward this call to the AutomateRoot
    It returns the number of used edges (not nodes)*/
    unsigned int connectionCount();

  //TODO make private later and or remove it
    /*! You need this for direct data access, use with care! Can be modified if no view is open. If
        any active view is open, close it first OR enforce a reset() call on all active views after
        your direct data access is finished.
        Call reset() in this class afterwards, which will update all views. Keep in mind that this
        will reset all your customized layouts!*/
    AbstractTreeItem* automateRootPtr();
    /*! A custom name to identify your automate */
    QString name;
    /*! Calling reset() in this class will update all views. Keep in mind that this
    will reset all your customized layouts!
    YOU HAVE TO DO THAT if you modify the data directly while any view is open. If no
    view is active reset() won't have any effect. */
    void reset();
    /*! If the layout of the data was changed, call this function instead of reset()*/
    void layoutChanged();
  private:
    /*! This is the pointer to the data structure representing the automate */
    AutomateRoot* root;
    /*! This is the pointer to the model. */
    Model* m_model;
#ifdef MODELTEST
    ModelTest* modeltest;
#endif
};

#endif
