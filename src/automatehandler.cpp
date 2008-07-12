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

#include "automatehandler.h"

automatehandler::automatehandler( QWidget* parent ) : QDialog( parent ) {
  setAttribute( Qt::WA_DeleteOnClose );
  setupUi( this );
  connect( treeWidget, SIGNAL( customContextMenuRequested( const QPoint & ) ),
           this, SLOT( popQMenu( const QPoint & ) ) );
  connect( updateBtn, SIGNAL( clicked() ), this, SLOT( updateTreeWidget() ) );
  qsrand(0);
  addRandomAutomate();
  addRandomAutomate();
  addRandomAutomate();
  addRandomAutomate();
  addRandomAutomate();
  addRandomAutomate();
  addRandomAutomate();
  addRandomAutomate();
  addRandomAutomate();
}

automatehandler::~automatehandler() {
  // see quit()
}

void automatehandler::updateTreeWidget() {
  treeWidget->clear();
  for ( int i = 0; i < automates.size(); ++i ) {
    QTreeWidgetItem *a = new QTreeWidgetItem( treeWidget );
    a->setData( 0, customRole::IdRole, i );
    a->setText( 0, automates[i]->name );
    a->setText( 1, QString( "%1" ).arg( automates[i]->childCount() ) );
    a->setText( 2, QString( "%1" ).arg( automates[i]->connectionCount() ) );
    a->setText( 3, tr( "0" ) );
    a->setText( 4, tr( "0" ) );
  }
  treeWidget->resizeColumnToContents( 0 );
  treeWidget->resizeColumnToContents( 1 );
  treeWidget->resizeColumnToContents( 2 );
  treeWidget->resizeColumnToContents( 3 );
  treeWidget->resizeColumnToContents( 4 );
}

void automatehandler::addAutomate() {
  automate* myautomate1 = new automate;
  automates.push_back( myautomate1 );
  updateTreeWidget();
  qDebug( "automate added" );
}

void automatehandler::addRandomAutomate() {
automate* myautomate1 = new automate;
  automates.push_back( myautomate1 );

  //TODO fix this warning, fix everything!
  //WARNING BEGIN
  //  the code below will not work, once the model is finalized
  //  until then, it will remain to test the automate class
  //  the automateRoot() function will be made protected
  //  and not pulic as it is right now!
  AbstractTreeItem* rootnode = myautomate1->automateRootPtr();
  AutomateRoot* r = (AutomateRoot*)rootnode;
  r->symbol("a");
  r->symbol("Q");
  r->symbol("f");
  r->symbol("_%");
//   qDebug() << "rootnode=" << (unsigned int) rootnode;
//   qDebug() << "rootnode.parent()=" << (unsigned int)rootnode->parent();

  int todonodes = qrand() % 20; //20
  int todoconnections_ = 11;    //44 (first graph, connection c3 remove -> ctrl+u -> segfault

  for ( int i = 0; i < todonodes; ++i ) {
    int s = qrand() % 2;
    int f = qrand() % 2;

    node* node1 = new node( rootnode );
    rootnode->appendChild( node1 );
    node1->setProperty( "start", s );
    node1->setProperty( "final", f );
  }

  for ( int i = 0; i < todonodes; ++i ) {
    int todoconnections = qrand() % todoconnections_;
    for ( int x = 0; x < todoconnections; ++x ) {
      // pick a node

      int rand = qrand();
      int nodes = rootnode->childCount();
      int pick = rand % nodes;

      if ( pick >= nodes ) {
        qDebug() << "FATAL ERROR: choosing node " << pick << " out of " << nodes << " nodes";
        exit( 0 );
      }

      AbstractTreeItem* z = rootnode->child( pick );
      node* node1 = static_cast<node*>( z );

      node_connection* nc1 =  new node_connection( node1 );
      nc1->setSymbol_index (qrand() % r->size());
      nc1->setNext_node( rootnode->child( qrand() % rootnode->childCount() ));
      // add connection to the picked node
      node1->appendChild( static_cast<AbstractTreeItem*>( nc1 ) );
    }
  }
  //WARNING END

  updateTreeWidget();
//   qDebug("random automate added");
}

void automatehandler::delAutomate() {
//WARNING::this code has to be checked. it might delete the wrong
//         elements on multiple selection delete
  for ( int i = 0; i < treeWidget->selectedItems().size(); ++i ) {
    qDebug( "delAutomate::deleting automate" );
    QTreeWidgetItem * item  = treeWidget->selectedItems()[i];
    if ( item == NULL )
      return;
    int z = item->data( 0, customRole::IdRole ).toInt();
    delete automates[z];
    automates.remove( z );
    updateTreeWidget();
  }
}

void automatehandler::copyAutomate() {
  qDebug() << "TODO::copyAutomate";
  QMessageBox::information( this, "not implemented yet", "not done yet", QMessageBox::Ok );

  /*  for(int i=0; i < treeWidget->selectedItems().size(); ++i) {
      qDebug("cpyAutomate::copying automate");
      QTreeWidgetItem * item  = treeWidget->selectedItems()[i];
      if (item == NULL)
        return;
      QString a = item->data(0,customRole::IdRole).toInt();
      int z = a.toInt();

      automate* n = new automate;
      *n = *(automates[z]);

      automates.push_back(n);
      updateTreeWidget();
    }*/
  updateTreeWidget();
}

void automatehandler::popQMenu( const QPoint  & point ) {
  QTreeWidgetItem * item = treeWidget->itemAt( point ) ;

  QMenu qm( "automate interaction", treeWidget );

  // ONE automate selected
  if ( item != 0 ) {
    qm.addAction( "dump automate", this, SLOT( dumpAutomate() ) );
    qm.addAction( QIcon( ":/icons/gtk-close.png" ), "remove automate", this, SLOT( delAutomate() ) );
    qm.addAction( QIcon( ":/icons/assign.png" ), "copy automate", this, SLOT( copyAutomate() ) );
    qm.addSeparator();
    qm.addAction( "detect automate type", this, SLOT( todo() ) );
    qm.addAction( "minimize", this, SLOT( todo() ) );
    QString efreestring = QString( "make %1-free" ).arg( QChar(( unsigned short ) 949 ) );
    qm.addAction( efreestring, this, SLOT( todo() ) );
    qm.addAction( "DFA 2 NFA", this, SLOT( todo() ) );
    qm.addAction( "invert All connections", this, SLOT( todo() ) );

    qm.addSeparator();
    qm.addAction( "new graphicsview", this, SLOT( openNewGraphicsView() ) );
    qm.addAction( "new treeview", this, SLOT( openNewTreeView() ) );
  }
  // NO automate selected
  qm.addSeparator();
  qm.addAction( QIcon( ":/icons/gtk-add.png" ), "New empty Automate", this, SLOT( addAutomate() ) );
  qm.addAction( QIcon( ":/icons/gtk-add.png" ), "New random Automate", this, SLOT( addRandomAutomate() ) );
//    qm.addAction("Close all views", this, SLOT(closeAllViews()));
  qm.addSeparator();

  if ( item != NULL ) {
    int z = item->data( 0, customRole::IdRole ).toInt();
    for ( int i = 0; i < automates[z]->vh->getListOfViews().size(); ++i ) {
      AbstractView* av = automates[z]->vh->getListOfViews()[i];
      QString objectname = av->windowTitle().split( " " ).first();
      QString viewName = QString( "%1 %2" ).arg( objectname ).arg( i );
      qm.addAction( viewName, av, SLOT( showWithFocus() ) );
    }
  }
  qm.exec( QCursor::pos() );
  treeWidget->mapToGlobal( point );
}

void automatehandler::openNewGraphicsView() {
  openNewView( GraphicsViewType );
}

void automatehandler::openNewTreeView() {
  openNewView( TreeViewType );
}

void automatehandler::openNewView( ViewType v ) {
  for ( int i = 0; i < treeWidget->selectedItems().size(); ++i ) {
    QTreeWidgetItem * item  = treeWidget->selectedItems()[i];
    if ( item == NULL )
      return;
    int z = item->data( 0, customRole::IdRole ).toInt();
    automates[z]->openNewView( v );
  }
}

void automatehandler::dumpAutomate() {
  for ( int i = 0; i < treeWidget->selectedItems().size(); ++i ) {
    qDebug( "delAutomate::deleting automate" );
    QTreeWidgetItem * item  = treeWidget->selectedItems()[i];
    if ( item == NULL )
      return;
    int z = item->data( 0, customRole::IdRole ).toInt();
    automates[z]->dump();
  }
}

void automatehandler::todo() {
  qDebug() << "FIXME: not implemneted yet";
  QMessageBox::information( this, "not implemented yet", "not done yet", QMessageBox::Ok );
}

void automatehandler::closeEvent( QCloseEvent * /*event*/ ) {
  qDebug() << "closeEvent";
}

void automatehandler::keyPressEvent( QKeyEvent * keyEvent ) {
  int z = -1;
  if (treeWidget->selectedItems().size() == 1) {
    QTreeWidgetItem * item  = treeWidget->selectedItems().first();
    if ( item != NULL ) {
      z = item->data( 0, customRole::IdRole ).toInt();
    }
  }
  if ( keyEvent->key() == Qt::Key_T ) {
    if (z >= 0)
      automates[z]->openNewView( TreeViewType );
  }
  if ( keyEvent->key() == Qt::Key_G ) {
    if (z >= 0)
      automates[z]->openNewView( GraphicsViewType );
  }
  if ( keyEvent->key() == Qt::Key_Escape ) {
    quit();
  }
}

void automatehandler::quit() {
  qDebug( "automatehandler::~automatehandler" );
  for ( int i = 0; i < automates.size(); ++i ) {
    delete automates[i];
  }
  automates.clear();
  qDebug() << "program is now exited with exit(0);";
  exit(0);
}


