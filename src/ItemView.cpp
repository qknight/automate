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

ItemView::ItemView( QGraphicsView* view, Model *model, QWidget * parent ) : QAbstractItemView(parent) {
  this->view = view;
  this->model = model;
  setModel( model );
  scene = new GraphicsScene( model );

  view->setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );
  view->setScene( scene );
  view-> setDragMode (QGraphicsView::RubberBandDrag);

//   SceneItem_FlexibleConnection* flex = new SceneItem_FlexibleConnection(scene);
//   scene->addItem(flex);

  // Special layout functionality should go here!
  processNewNodes();
  connect(scene, SIGNAL(hideView()), parentWidget (), SLOT(hide()));
}

ItemView::~ItemView() { }

QRect ItemView::visualRect( const QModelIndex &/*index*/ ) const {
  return QRect()/*view->rect()*/;
}

void ItemView::scrollTo( const QModelIndex &/*index*/, ScrollHint /*hint*/ ) {

}

QModelIndex ItemView::indexAt( const QPoint &/*point*/ ) const {
  return QModelIndex();
}

QModelIndex ItemView::moveCursor( CursorAction /*cursorAction*/, Qt::KeyboardModifiers /*modifiers*/ ) {
  return QModelIndex();
}

int ItemView::horizontalOffset() const {
  return 0;
}

int ItemView::verticalOffset() const {
  return 0;
}

bool ItemView::isIndexHidden( const QModelIndex &/*index*/ ) const {
  return false;
}

void ItemView::setSelection( const QRect &/*rect*/, QItemSelectionModel::SelectionFlags /*command*/ ) {

}

QRegion ItemView::visualRegionForSelection( const QItemSelection &/*selection*/ ) const {
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
  qDebug() << "rowsInserted in ItemView called: need to insert " << end-start+1 << " item(s).";
  for (int i = start; i <= end; ++i) {
    QModelIndex item = model->index( i, 0, parent );
    if (model->getTreeItemType( item ) == NODE)
      scene->addNode( QPersistentModelIndex( item ) );
    else if (model->getTreeItemType( item ) == NODE_CONNECTION)
      scene->addConnection( QPersistentModelIndex( item ) );
  }
}

void ItemView::rowsAboutToBeRemoved( const QModelIndex & parent, int start, int end ) {
  qDebug() << "rowsAboutToBeRemoved in ItemView called: need to remove " << end-start+1 << " item(s).";
  for (int i = start; i <= end; ++i) {
    QModelIndex item = model->index( i, 0, parent );
    if (model->getTreeItemType( item ) == NODE)
      scene->removeNode( QPersistentModelIndex( item ) );
    else if (model->getTreeItemType( item ) == NODE_CONNECTION)
      scene->removeConnection( QPersistentModelIndex( item ) );
  }
}

void ItemView::dataChanged( const QModelIndex & topLeft, const QModelIndex & bottomRight ) {
  //TODO find all items which need to be updated, somewhere between topLeft and bottomRight
  //  topleft -- itemA
  //          -- itemB
  //          -- itemC
  //          -- bottomRight
  qDebug() << topLeft.row() << " " << topLeft.column();
  if (topLeft == bottomRight)
    qDebug() << "match, the two modelindexes are equal";
  else
    qDebug() << "WARNING: this has to be handled but isn't yet";

  if (model->getSelectedItemType(topLeft) == NODE) {
    qDebug() << "Node modification";
    scene->modifyNode(QPersistentModelIndex(topLeft));
  }
  if (model->getSelectedItemType(topLeft) == NODE_CONNECTION) {
    qDebug() << "Node_CONNECTION modification";
    scene->modifyConnection(QPersistentModelIndex(topLeft));
  }
  qDebug( "dataChanged in ItemView called" );
}

void ItemView::reset() {
//   scene->reset();
//   processNewNodes();
}

