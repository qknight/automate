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

ItemView::ItemView( QGraphicsView* view, GraphicsScene* scene, Model *model, QWidget * parent ) : QAbstractItemView( parent ) {
  this->view = view;
  this->model = model;
  this->scene = scene;
  setModel( model );
  want_antialiasing = true;
  view->setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );
  view->setScene( scene );
  view->setDragMode( QGraphicsView::RubberBandDrag );

//   SceneItem_FlexibleConnection* flex = new SceneItem_FlexibleConnection(scene);
//   scene->addItem(flex);

  // Special layout functionality should go here!
  processNewNodes();
}

ItemView::~ItemView() { }

void ItemView::toggleRenderHints() {
  want_antialiasing = !want_antialiasing;
  if ( want_antialiasing )
    view->setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );
  else
    view->setRenderHints( QPainter::SmoothPixmapTransform );
}

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
    scene->nodeInserted( QPersistentModelIndex( item ) );
  }
  for ( int i = 0; i < model->rowCount( QModelIndex() ); ++i ) {
    QModelIndex item = model->index( i, 0, QModelIndex() );
    for ( int x = 0; x < model->rowCount( item ); ++x ) {
      QModelIndex citem = model->index( x, 0, item );
      scene->connectionInserted( QPersistentModelIndex( citem ) );
    }
  }
}

void ItemView::rowsInserted( const QModelIndex & parent, int start, int end ) {
  qDebug() << "rowsInserted in ItemView called: need to insert " << end - start + 1 << " item(s).";
  for ( int i = start; i <= end; ++i ) {
    QModelIndex item = model->index( i, 0, parent );
    if ( model->getTreeItemType( item ) == NODE )
      scene->nodeInserted( QPersistentModelIndex( item ) );
    else
      if ( model->getTreeItemType( item ) == NODE_CONNECTION )
        scene->connectionInserted( QPersistentModelIndex( item ) );
  }
}

void ItemView::rowsAboutToBeRemoved( const QModelIndex & parent, int start, int end ) {
//   qDebug() << "rowsAboutToBeRemoved in ItemView called: need to remove " << end-start+1 << " item(s).";
  for ( int i = start; i <= end; ++i ) {
    QModelIndex item = model->index( i, 0, parent );
    if ( model->getTreeItemType( item ) == NODE )
      scene->nodeRemoved( QPersistentModelIndex( item ) );
    else
      if ( model->getTreeItemType( item ) == NODE_CONNECTION )
        scene->connectionRemoved( QPersistentModelIndex( item ) );
  }
}

/*
** This algorithm recurses trough the QModelIndex hierarchy
**  topleft -- itemA -- connection1
**             \---- -- connection2       given the topLeft item it returns itemA
**          -- itemB                      given itemA it returns connection1
**             \---- -- connection1       given connection1 it returns itemB
**          -- itemC                      ...
**          -- itemD (bottomRight)        and so on
**             \---- -- connection1
**             \---- -- connection2     <- given this last item, it returns QModelIndex()
*/
QModelIndex ItemView::recurseTroughIndexes( QModelIndex index ) {
//   qDebug() << "  " << index.row() << " ";
  // 1. dive deep into the structure until we found the bottom (not bottomRight)
  QModelIndex childIndex = model->index(0,0,index);
//   qDebug() << "step a";
  if (childIndex.isValid())
    return childIndex;

  // 2. now traverse all elements in the lowest hierarchy
  QModelIndex tmpIndex = model->index(index.row()+1,0,model->parent(index));//index.sibling(index.row()+1,0);
//   qDebug() << "step b";
  if (tmpIndex.isValid())
    return tmpIndex;

  // 3. if no more childs are found, return QModelIndex()
//   qDebug() << "step c";
  return QModelIndex();
}

/*
** we have to check all items between topLeft and bottomRight, so let's update all QModelIndex'es
** in between -> here comes recursion in handy.
*/
void ItemView::dataChanged( const QModelIndex & topLeft, const QModelIndex & bottomRight ) {
  QModelIndex tmpIndex  = topLeft;
  do {
//     qDebug() << "dataChanged is now called()";
    switch (model->getSelectedItemType( tmpIndex )) {
      case NODE:
//       qDebug() << __FUNCTION__ << "Node modification";
      scene->updateNode( QPersistentModelIndex( tmpIndex ) );
      break;
    case NODE_CONNECTION:
//       qDebug() << __FUNCTION__ << "Connection modification";
      scene->updateConnection( QPersistentModelIndex( tmpIndex ) );
      break;
      default:
        //FIXME this could be an issue
        qDebug() << __FILE__ << __FUNCTION__ << " didn't understand what i should be doing";
        exit(0);
    }
    if (tmpIndex == bottomRight)
      break;
    tmpIndex = recurseTroughIndexes( tmpIndex );
  } while ( tmpIndex.isValid());
}

void ItemView::reset() {
  // FIXME this should really be implemented!!!
//   scene->reset();
//   processNewNodes();
}

