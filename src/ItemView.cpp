//
// C++ Implementation: ItemView
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "ItemView.h"
#include "SceneItem_FlexibleConnection.h"

ItemView::ItemView( QGraphicsView* view, Model *model ) : QAbstractItemView() {
  this->view = view;
  this->model = model;
  setModel( model );
  scene = new GraphicsScene( model );

  view->setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );
  view->setScene( scene );
//   view->setRubberBandSelectionMode(Qt::ContainsItemShape);
  view-> setDragMode (QGraphicsView::RubberBandDrag);
//   SceneItem_FlexibleConnection* flex = new SceneItem_FlexibleConnection(scene);
//   scene->addItem(flex);

    processNewNodes();
}

ItemView::~ItemView() {

}

QRect ItemView::visualRect( const QModelIndex &index ) const {
  return QRect()/*view->rect()*/;
}

void ItemView::scrollTo( const QModelIndex &index, ScrollHint hint ) {

}

QModelIndex ItemView::indexAt( const QPoint &point ) const {
  return QModelIndex();
}

QModelIndex ItemView::moveCursor( CursorAction cursorAction, Qt::KeyboardModifiers modifiers ) {
  return QModelIndex();
}

int ItemView::horizontalOffset() const {
  return 0;
}

int ItemView::verticalOffset() const {
  return 0;
}

bool ItemView::isIndexHidden( const QModelIndex &index ) const {
  return false;
}

void ItemView::setSelection( const QRect &rect, QItemSelectionModel::SelectionFlags command ) {

}

QRegion ItemView::visualRegionForSelection( const QItemSelection &selection ) const {
  return QRegion();
}

void ItemView::processNewNodes() {
  for ( int i = 0; i < model->rowCount( QModelIndex() ); ++i ) {
    QModelIndex item = model->index( i, 0, QModelIndex() );
    scene->addNode( QPersistentModelIndex( item ) );
  }
  for ( int i = 0; i < model->rowCount( QModelIndex() ); ++i ) {
    QModelIndex item = model->index( i, 0, QModelIndex() );
    for ( int x = 0; x < model->rowCount( item ); ++x ) {
      QModelIndex citem = model->index( x, 0, item );
      scene->addConnection( QPersistentModelIndex( citem ) );
    }
  }
}

void ItemView::rowsInserted( const QModelIndex & parent, int start, int end ) {
//   QModelIndex item = model->index( i, 0, QModelIndex() );
//   scene->addNode( QPersistentModelIndex( parent ) );
  qDebug() << "rowsInserted in ItemView called: " << model->objectTypeQString(model->getTreeItemType( parent));
}

void ItemView::rowsAboutToBeRemoved( const QModelIndex & parent, int start, int end ) {
  qDebug( "rowsAboutToBeRemoved in ItemView called" );
}

void ItemView::dataChanged( const QModelIndex & topLeft, const QModelIndex & bottomRight ) {
//   topLeft == bottomRight
  qDebug( "dataChanged in ItemView called" );
}

void ItemView::reset() {
//   scene->reset();
//   processNewNodes();
}

