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

#include "treeView.h"

treeView::treeView( Model* model, QDialog* parent ) : AbstractView( parent ) {
  setupUi( this );
  this->model = model;

  proxyModel = new QSortFilterProxyModel( this );
  proxyModel->setSourceModel( model );

  ism = new QItemSelectionModel( proxyModel, this );

  debugTreeView->setModel( model );
  debugTreeView->resizeColumnToContents( 0 );
  debugTreeView->setColumnWidth( 0, 70 );
  debugTreeView->resizeColumnToContents( 1 );
  debugTreeView->resizeColumnToContents( 2 );
  debugTreeView->resizeColumnToContents( 3 );
  debugTreeView->resizeColumnToContents( 4 );
  debugTreeView->resizeColumnToContents( 5 );
  nodeTreeView->sortByColumn( 3, Qt::AscendingOrder );
  proxyModel->setDynamicSortFilter( true );
  proxyModel-> setFilterKeyColumn( -1 );

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
           this, SLOT( addNode() ) );
  connect( delNodeBtn, SIGNAL( clicked() ),
           this, SLOT( delSelectedNodes() ) );
  connect( addConnectionBtn, SIGNAL( clicked() ),
           this, SLOT( addConnection() ) );
  connect( delConnectionBtn, SIGNAL( clicked() ),
           this, SLOT( delSelectedNodes() ) );

  connect( ism, SIGNAL( currentChanged( const QModelIndex &, const QModelIndex & ) ),
           this, SLOT( currentChanged( const QModelIndex &, const QModelIndex & ) ) );
  connect( lineEdit, SIGNAL(
             textChanged( QString ) ),
           this, SLOT( setFilter( QString ) ) );
}

void treeView::currentChanged( const QModelIndex & current, const QModelIndex & /*previous*/ ) {
  QString a;
  QModelIndex currentItem = proxyModel->mapToSource( current );
  if ( !currentItem.isValid() )
    return;
  switch ( model->getSelectedItemType( currentItem ) ) {
  case AUTOMATE_ROOT:
    a = "AUTOMATE_ROOT";
    delConnectionBtn->setEnabled( false );
    delNodeBtn->setEnabled( false );
    addConnectionBtn->setEnabled( false );
    break;
  case NODE:
    a = "NODE";
    delNodeBtn->setEnabled( true );
    delConnectionBtn->setEnabled( false );
    addConnectionBtn->setEnabled( true );
    break;
  case NODE_CONNECTION:
    a = "NODE_CONNECTION\n";
    delNodeBtn->setEnabled( false );
    delConnectionBtn->setEnabled( true );
    addConnectionBtn->setEnabled( true );
    a.append( "0 - not defined yet\n" )    ;
    a.append( "1 - epsilon connection\n" );
    a.append( "2 - 'a'\n" );
    a.append( "3 - 'b'\n" );
    a.append( "4 - 'c'\n" );
    //TODO read the symbol2int object to find out about defined connection symbols
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

void treeView::delSelectedNodes( ) {
  int selectedcount = ism->selectedRows().size();
  qDebug( "%i selected item(s) to remove", selectedcount );
  QList<QModelIndex> selectedItems;
  foreach( QModelIndex selectedItem, ism->selectedIndexes() )
  selectedItems.append( proxyModel->mapToSource( selectedItem ) );
  if ( model->removeNodes( selectedItems ) )
    qDebug() << "success removing all selected nodes";
  else
    qDebug() << "FAILED removing all selected nodes";
}

void treeView::addNode() {
  addAbstractNodeItem( NODE );
}

void treeView::addConnection() {
  addAbstractNodeItem( NODE_CONNECTION );
}

void treeView::addAbstractNodeItem( TreeItemType type ) {
  //FIXME this code needs a cleanup
  // it's still unclear how to handle multiple insertions on multiple selections
  // it might be wise to only allow appending of items for 'one' selected item
  int selectedcount = ism->selectedRows().size();
  qDebug( "%i item(s) need to be appended", selectedcount );
  QList<QModelIndex> selectedItems;
  foreach( QModelIndex selectedItem, ism->selectedRows() )
    selectedItems.append( proxyModel->mapToSource( selectedItem ) );
  if (selectedcount == 0)
    selectedItems.append(QModelIndex());
  foreach( QModelIndex item, selectedItems ) {
    switch ( type ) {
    case NODE:
      qDebug() << "addNODE clicked";
      model->insertRows( model->rowCount(QModelIndex()), 1 );
      continue;
    case NODE_CONNECTION:
      qDebug() << "addNODE_CONNECTION clicked";
      if ( model->getTreeItemType( item ) == NODE ) {
        model->insertRows( model->rowCount(item), 1, item );
      }  else if ( model->getTreeItemType( item ) == NODE_CONNECTION ) {
        QModelIndex parentItem = model->parent( item );
        model->insertRows( model->rowCount(parentItem), 1, parentItem );
        }
      continue;
    }
  }
}

void treeView::setFilter( QString filterText ) {
  proxyModel->setFilterRegExp( QRegExp( filterText, Qt::CaseInsensitive,
                                        QRegExp::FixedString ) );
}
