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


#ifndef TREEVIEW__HH__
#define TREEVIEW__HH__

#include "ui_treeViewMainWindow.h"
#include "Model.h"
#include "AbstractView.h"

#include <QVector>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QItemSelectionModel>
#include <QKeyEvent>

/*! the treeView is one of the two main views which binds to the model */
class treeView : public AbstractView, public Ui::treeViewMainWindow {
    Q_OBJECT
  private:
    /*! a selection model used to query item selections from the QTreeView */
    QItemSelectionModel* ism;
    /*! proxy model is used to sort the elements in the view */
    QSortFilterProxyModel *proxyModel;
    /*! this code inserts a node or a connection depending on the selection of items, can insert
    ** multiple elements at once */
    void addAbstractNodeItem( TreeItemType type );
    /*! the treeview has shortcuts, see the source */
    void keyPressEvent( QKeyEvent * keyEvent );
    /*! toggles the start/final role of a connection*/
    void startToggleEvent(int role);
    /*! removes all selected elements of a QTreeView */
    void removeEvent();
  public:
    /*! ... */
    treeView( Model *, QMainWindow* parent = 0 );
    /*! ... */
    Model *model;
  public slots:
    /*! adds a node */
    void addNode();
    /*! adds a connection */
    void addConnection();
    /*! removes the selected items */
    void delSelectedItems();
  private slots:
    /*! when the selection changes this will change the info on the current main selected item*/
    void currentChanged( const QModelIndex & current, const QModelIndex & previous );
};

#endif
