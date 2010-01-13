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
#include "ui_AutomateHandlerWidget.h"

/*! this is the base class which handles all automates and represents them in a nice list. */
class automatehandler : public QDialog, private Ui::controllerWidget {
    Q_OBJECT
  public:
    /*! constructor */
    automatehandler( QWidget* parent = 0 );
    /*! destructor */
    ~automatehandler();
  private:
    /*! internal storage of automate* */
    QVector<automate*> automates;
    /*! 'g' opens a graphicsView, 't' opens a treeView */
    void keyPressEvent( QKeyEvent * keyEvent );
  private slots:
    /*! triggers an update of node/connection count, this must be done manually right now */
    void updateTreeWidget();
    /*! adds a new empty automate to the handler */
    void addAutomate();
    /*! adds a new random automate to the handler */
    void addRandomAutomate();
    /*! delets the currently selected automate */
    void delAutomate();
    /*! clones the selected automate - not implemented yet */
    void copyAutomate();
    /*! dumps the current automate */
    void dumpAutomate();

    /*! generic view open handler, see ViewType argument which views are usable */
    void openNewView( ViewType );
    /*! opens a graphicsView for the currently selected automate*/
    void openNewGraphicsView();
    /*! opens a treeView for the currently selected automate */
    void openNewTreeView();
    /*! context menu stuff */
    void popQMenu( const QPoint & );
    /*! indicates that a function isn't implemented yet on stdout */
    void todo();
    /*! quits the application */
    void quit();
};

#endif
