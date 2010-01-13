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
class TreeView : public AbstractView, public Ui::treeViewMainWindow {
    Q_OBJECT
  private:
    /*! a selection model used to query item selections from the QTreeView */
    QItemSelectionModel* ism;
    /*! proxy model is used to sort the elements in the view */
    QSortFilterProxyModel *proxyModel;
    /*! the treeview has shortcuts, see the source */
    void keyPressEvent( QKeyEvent * keyEvent );
    /*! toggles the start/final role of a connection*/
    void startToggleEvent(int role);
    /*! removes all selected elements of a QTreeView */
    void removeEvent();
    /*! all selected QModelIndex'es are used to add a connection. if the selected QModelIndex is a connection
        itself nothing happens but if it is a node a connection will be appended.*/
    void addConnection();
  public:
    /*! TODO */
    TreeView( Model *, QMainWindow* parent = 0 );
    /*! TODO */
    ~TreeView();
    /*! holds a pointer to the model used. a Automate class has only one model but can have several views that
        share the same model */
    Model *model;
  public slots:
    /*! adds a node */
    void addNodeSlot();
    /*! adds a connection */
    void addConnectionSlot();
    /*! removes the selected items */
    void delSelectedItems();
  private slots:
    /*! when the selection changes this will change the info on the current main selected item*/
    void currentChanged( const QModelIndex & current, const QModelIndex & previous );
};

#endif
