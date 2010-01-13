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

#include "ItemView.h"

ItemView::ItemView( QGraphicsView* view, GraphicsScene* scene, Model *model, QWidget * parent ) : QAbstractItemView( parent ) {
  connect(scene, SIGNAL(reset()), this, SLOT(reset()));
  connect(this, SIGNAL(clearScene()), scene, SLOT(clearScene()));
  this->view = view;
  this->model = model;
  this->scene = scene;
  setModel( model );
  want_antialiasing = true;
//   view->setDragMode(QGraphicsView::RubberBandDrag);
//   view->setDragMode(QGraphicsView::ScrollHandDrag);
  view->setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );
  view->setScene( scene );

/*#ifndef QT_NO_OPENGL
  openGlButton->setEnabled(QGLFormat::hasOpenGL());
#else
  openGlButton->setEnabled(false);
#endif

#ifndef QT_NO_OPENGL
  graphicsView->setViewport(openGlButton->isChecked() ? new QGLWidget(QGLFormat(QGL::SampleBuffers)) : new QWidget);
#endif
  view->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)))*/;

  //   SceneItem_FlexibleConnection* flex = new SceneItem_FlexibleConnection(scene);
//   scene->addItem(flex);

  // Special layout functionality should go here!
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

void ItemView::reset() {
//   qDebug() << __PRETTY_FUNCTION__;
  emit clearScene();
  init();
}

void ItemView::init() {
//   qDebug() << __PRETTY_FUNCTION__;
  for ( int i = 0; i < model->rowCount( QModelIndex() ); ++i ) {
//     qDebug() << "adding node i =" << i;
    QModelIndex item = model->index( i, 0, QModelIndex() );
    scene->nodeInserted( QPersistentModelIndex( item ) );
  }
  for ( int i = 0; i < model->rowCount( QModelIndex() ); ++i ) {
//     qDebug() << "adding connection to node i =" << i;
    QModelIndex item = model->index( i, 0, QModelIndex() );
    for ( int x = 0; x < model->rowCount( item ); ++x ) {
//       qDebug() << "adding connection x =" << x;
      QModelIndex citem = model->index( x, 0, item );
      scene->connectionInserted( QPersistentModelIndex( citem ) );
    }
  }
//   qDebug() << __FUNCTION__ << "END";
}

void ItemView::rowsInserted( const QModelIndex & parent, int start, int end ) {
//   qDebug() << "rowsInserted in ItemView called: need to insert " << end - start + 1 << " item(s).";
  for ( int i = start; i <= end; ++i ) {
    QModelIndex item = model->index( i, 0, parent );
    if ( model->data( item, customRole::TypeRole ).toInt() == ViewTreeItemType::NODE )
      scene->nodeInserted( QPersistentModelIndex( item ) );
    else if ( model->data( item, customRole::TypeRole ).toInt() == ViewTreeItemType::NODE_CONNECTION )
      scene->connectionInserted( QPersistentModelIndex( item ) );
  }
}

void ItemView::rowsAboutToBeRemoved( const QModelIndex & parent, int start, int end ) {
//   qDebug() << "rowsAboutToBeRemoved in ItemView called: need to remove " << end-start+1 << " item(s).";
  for ( int i = start; i <= end; ++i ) {
    QModelIndex item = model->index( i, 0, parent );
    if ( model->data( item, customRole::TypeRole ).toInt() == ViewTreeItemType::NODE )
      scene->nodeRemoved( QPersistentModelIndex( item ) );
    else if ( model->data( item, customRole::TypeRole ).toInt() == ViewTreeItemType::NODE_CONNECTION )
      scene->connectionRemoved( QPersistentModelIndex( item ) );
  }
}

/*!
** This algorithm traverses trough the QModelIndex hierarchy
**  topleft -- itemA -- connection1
**             \---- -- connection2       given the topLeft item it returns itemA
**          -- itemB                      given itemA it returns connection1
**             \---- -- connection1       given connection1 it returns itemB
**          -- itemC                      ...
**          -- itemD (bottomRight)        and so on
**             \---- -- connection1
**             \---- -- connection2     <- given this last item, it returns QModelIndex()
*/
QModelIndex ItemView::traverseTroughIndexes( QModelIndex index ) {
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

void ItemView::dataChanged( const QModelIndex & topLeft, const QModelIndex & bottomRight ) {
//   qDebug() << __FUNCTION__;
  QModelIndex tmpIndex = topLeft;
  do {
//     qDebug() << "dataChanged is now called()";
    switch (model->data( tmpIndex, customRole::TypeRole ).toInt()) {
      case ViewTreeItemType::NODE:
//        qDebug() << __FUNCTION__ << "Node modification";
        scene->updateNode( QPersistentModelIndex( tmpIndex ) );
        break;
      case ViewTreeItemType::NODE_CONNECTION:
//        qDebug() << __FUNCTION__ << "Connection modification";
        scene->updateConnection( QPersistentModelIndex( tmpIndex ) );
        break;
      default:
        qDebug() << __PRETTY_FUNCTION__ << " didn't understand what i should be doing";
        exit(0);
    }
    if (tmpIndex == bottomRight)
      break;
    tmpIndex = traverseTroughIndexes( tmpIndex );
  } while ( tmpIndex.isValid());
}

void ItemView::layoutChanged(){
  //FIXME do we need that?
  qDebug() << __PRETTY_FUNCTION__ << " is NOT implemented yet, please implement me!, exiting";
  exit(0);
}
