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

#ifndef TREEVIEW__HH__
#define TREEVIEW__HH__

#include "ui_treeViewWidget.h"
#include "Model.h"
#include "AbstractView.h"

#include <QVector>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QItemSelectionModel>

class treeView : public AbstractView, public Ui::treeViewWidget {
    Q_OBJECT

  private:
    QItemSelectionModel* ism;
    QSortFilterProxyModel *proxyModel;
    void addAbstractNodeItem( TreeItemType type );

  public:
    treeView( Model *, QDialog* parent = 0 );
    Model *model;
  public slots:
    void addNode();
    void addConnection();
    void delSelectedNodes();
  private slots:
    void setFilter( QString filterText );
    void currentChanged( const QModelIndex & current, const QModelIndex & previous );
};

#endif
