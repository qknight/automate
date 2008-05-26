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

#ifndef AUTOMATEHANDLER__HH__
#define AUTOMATEHANDLER__HH__

#include <QDialog>
#include <QMenu>
#include <QMessageBox>

#include "AbstractTreeItem.h"
#include "automate.h"
#include "node.h"
#include "node_connection.h"
#include "Model.h"

#include "treeView.h"

#include "ui_controllerWidget.h"

class automatehandler : public QDialog, private Ui::controllerWidget {
    Q_OBJECT

  private:
    QVector<automate*> automates;
    void closeEvent( QCloseEvent * event );
  public:
    automatehandler( QWidget* parent = 0 );
    ~automatehandler();
  private slots:
    void updateTreeWidget();
    void addAutomate();
    void addRandomAutomate();
    void delAutomate();
    void copyAutomate();
    void dumpAutomate();

    void openNewView( ViewType );
    void openNewGraphicsView();
    void openNewTreeView();
    void popQMenu( const QPoint & );
    void todo();
};

#endif
