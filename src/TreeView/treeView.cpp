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

#include "treeView.h"

TreeView::TreeView( Model* model, QMainWindow* parent ) : AbstractView( parent ) {
  setupUi( this );
  this->model = model;

  proxyModel = new QSortFilterProxyModel( this );
  proxyModel->setSourceModel( model );
  ism = new QItemSelectionModel( proxyModel, this );

  nodeTreeView->sortByColumn( 3, Qt::AscendingOrder );
  proxyModel->setDynamicSortFilter( true );
  proxyModel->setFilterKeyColumn( -1 );
  proxyModel->setSortRole ( customRole::SortRole );

  nodeTreeView->setModel( proxyModel );
  nodeTreeView->setSortingEnabled( true );
  nodeTreeView->setSelectionModel( ism );
  nodeTreeView->resizeColumnToContents( 0 );
  nodeTreeView->setColumnWidth( 0, 70 );
  nodeTreeView->resizeColumnToContents( 1 );
  nodeTreeView->resizeColumnToContents( 2 );
  nodeTreeView->resizeColumnToContents( 3 );
  nodeTreeView->resizeColumnToContents( 4 );
  nodeTreeView->resizeColumnToContents( 5 );

  connect( addNodeBtn, SIGNAL( clicked() ),
           this, SLOT( addNodeSlot() ) );
  connect( delNodeBtn, SIGNAL( clicked() ),
           this, SLOT( delSelectedItems() ) );
  connect( addConnectionBtn, SIGNAL( clicked() ),
           this, SLOT( addConnectionSlot() ) );
  connect( delConnectionBtn, SIGNAL( clicked() ),
           this, SLOT( delSelectedItems() ) );

  connect( ism, SIGNAL( currentChanged( const QModelIndex &, const QModelIndex & ) ),
           this, SLOT( currentChanged( const QModelIndex &, const QModelIndex & ) ) );
}

TreeView::~TreeView() {
//   qDebug() << __PRETTY_FUNCTION__;
  delete ism;
  delete proxyModel;
}

void TreeView::currentChanged( const QModelIndex & current, const QModelIndex & /*previous*/ ) {
//   qDebug() << __FUNCTION__;
  QString a;
  QModelIndex currentItem = proxyModel->mapToSource( current );
  if ( !currentItem.isValid() ) {
    textBrowser->setText( "no element selected" );
    return;
  }
  // this is wrong since it should use the QVariant QModelIndex::data ( int role = Qt::DisplayRole ) const
  // instead of adding another function into the model
  switch ( model->data( currentItem, customRole::TypeRole ).toInt() ) {
    case ViewTreeItemType::AUTOMATE_ROOT:
      a = "AUTOMATE_ROOT";
      delConnectionBtn->setEnabled( false );
      delNodeBtn->setEnabled( false );
      addConnectionBtn->setEnabled( false );
      break;
    case ViewTreeItemType::NODE:
      a = "NODE";
      delNodeBtn->setEnabled( true );
      delConnectionBtn->setEnabled( false );
      addConnectionBtn->setEnabled( true );
      break;
    case ViewTreeItemType::NODE_CONNECTION:
      a = "NODE_CONNECTION\n";
      delNodeBtn->setEnabled( false );
      delConnectionBtn->setEnabled( true );
      addConnectionBtn->setEnabled( true );
      a.append("\nInternal symbolTable:\n");
      for (int i=0; i < model->size(); ++i) {
	a.append(QString("%1   -   %2\n").arg(i).arg(model->symbol(i)));
      }
      break;
    default:
      delNodeBtn->setEnabled( false );
      a = "not in record, this should not happen";
      break;
  }

  QString text = QString( "type::%1\nid = %2" )
                 .arg( a )
                 .arg( model->data( currentItem, customRole::IdRole ).toString() );
  textBrowser->setText( text );
}

void TreeView::delSelectedItems( ) {
  QList<QPersistentModelIndex> selectedItems;
  foreach( QModelIndex selectedItem, ism->selectedRows() )
    selectedItems.append( QPersistentModelIndex(proxyModel->mapToSource( selectedItem ) ) );
//   qDebug( "%i selected item(s) to remove", selectedItems.size() );
  model->removeItems( selectedItems );
}

void TreeView::addNodeSlot() {
  model->insertNode();
}

void TreeView::addConnectionSlot() {
  addConnection();
}

void TreeView::keyPressEvent( QKeyEvent * keyEvent ) {
  if ( keyEvent->key() == Qt::Key_X ) {
    delSelectedItems();
  }
  if ( keyEvent->key() == Qt::Key_Escape ) {
    hide();
  }
  if ( keyEvent->key() == Qt::Key_N ) {
    model->insertNode();
  }
  if ( keyEvent->key() == Qt::Key_C ) {
    addConnection();
  }
  // node start toggle
  if ( keyEvent->key() == Qt::Key_S ) {
    startToggleEvent( customRole::StartRole );
  }
  // node final toggle
  if ( keyEvent->key() == Qt::Key_F ) {
    startToggleEvent( customRole::FinalRole );
  }
}

void TreeView::startToggleEvent( int role ) {
  int selectedcount = ism->selectedRows().size();
  QList<QModelIndex> selectedItems;
  foreach( QModelIndex selectedItem, ism->selectedRows() )
    selectedItems.append( proxyModel->mapToSource( selectedItem ) );

  if ( selectedcount == 1 ) {
    QModelIndex index = selectedItems.first();
    if ( model->data( index, customRole::TypeRole ).toInt() == ViewTreeItemType::NODE ) {
      bool state = model->data( index, role ).toBool();
      model->setData( index, !state, role );
    } else {
      qDebug() << "select a node to use this toggle";
    }
  } else {
    qDebug() << "select only one item to use the toggle";
  }
}

void TreeView::addConnection() {
//   qDebug( "%i item(s) selected", ism->selectedRows().size() );

  // will insert a connection if the parent item (the QModelIndex() is of type NODE)
  foreach( QModelIndex selectedItem, ism->selectedRows() ) {
    model->insertConnection(proxyModel->mapToSource( selectedItem ));  
  }
}
