//
// C++ Implementation: GraphicsScene
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "GraphicsScene.h"

GraphicsScene::GraphicsScene( Model *model ) : QGraphicsScene() {
  this->model = model;
}

GraphicsScene::~GraphicsScene() {

}

void GraphicsScene::selectionChanged() {
  qDebug( "Selection changed, %i selected items", selectedItems().size() );
}

void GraphicsScene::addNode( QPersistentModelIndex item ) {
  int id = model->data( item, customRole::IdRole ).toInt();
  bool start = model->data( item, customRole::StartRole ).toBool();
  bool final = model->data( item, customRole::FinalRole ).toBool();
  SceneItem_Node* node = new SceneItem_Node( item, start, final, QString( "%1" ).arg( id ) );
  node->setData( 0, &item );
  node->setPos( node->pos().x() + qrand() % 400, node->pos().y() + qrand() % 600 );
  addItem( node );
}

void GraphicsScene::addConnection( QPersistentModelIndex item ) {
//   int id = model->data( item, customRole::IdRole ).toInt();
  QGraphicsItem* a = modelToSceenIndex( QPersistentModelIndex( model->parent( item ) ) );
  if ( a == NULL )
    return;
  QModelIndex next_node_index = model->next_nodeModelIndex( item );
  if ( !next_node_index.isValid() ) {
    qDebug() << "Critical error because next_node isn't a valid index";
  }
  QGraphicsItem* b = modelToSceenIndex( next_node_index );
  if ( b == NULL )
    return;
  int symbol_index = model->data( item, customRole::IndexRole ).toInt();
  SceneItem_Connection * cItem = new SceneItem_Connection( item, symbol_index, ( SceneItem_Node * )a, ( SceneItem_Node * )b );
  cItem->setData( 0, &item );
  (( SceneItem_Node * )a )->addConnection( cItem );
  (( SceneItem_Node * )b )->addConnection( cItem );
  addItem( cItem );
}

void GraphicsScene::modifyNode( QPersistentModelIndex  ) {

}

void GraphicsScene::modifyConnection( QPersistentModelIndex item ) {
  // case 1. symbol_index changed
  qDebug() << "id of changed item " << model->data( item, customRole::IdRole ).toInt();
  unsigned int index = model->data( item, customRole::IndexRole ).toInt();
  QGraphicsItem* i = modelToSceenIndex( item );
  if ( i == NULL )
    return;
  if ( i->type() == SceneItem_ConnectionType ) {
    (( SceneItem_Connection* )i )->setSymbol_Index( index );
  }
  // case 2. next_node changed
  // check if next_node changed
  // unregister at next_node
  // register at new next_node
  // change item's new parentitem
  // update item
}

void GraphicsScene::reset() {
  qDebug() << "should call reset() in the GraphicsScene now";
}

/*
** the qgraphicsscene stores all graphical objects and in those objects
** we have a QPersistentModelIndex stored. this gives us the possibility of
** having several different graphicsViews on the same automate
*/

// FIXME i've implemented my own compare function: compareIndexes since this implementation doesn't use
// column BUT columns somehow where reported to be different, meaning: a stored index could have column 3
// while the treeView would make a difference because the treeView uses the columns to distinguish between
// different entries in the hierarchical view (the treeView) where for instance column 3 shows the node name
// and column 4 shows the symbol_index of a connection
QGraphicsItem* GraphicsScene::modelToSceenIndex( QPersistentModelIndex index ) {
  QList<QGraphicsItem *> m_list = items();
//   qDebug() << "=== searching in: " << m_list.size() << " items ====";
//   qDebug() << " searching for: " << index.row() <<  " " << index.column() << " row/column";
  for ( int i = 0; i < m_list.size(); ++i ) {
    if ( m_list[i]->type() == SceneItem_NodeType ) {
      if (compareIndexes((( SceneItem_Node * )m_list[i] )->index, index )) {
//         qDebug() << "node found";
        return m_list[i];
      }
    }
    if ( m_list[i]->type() == SceneItem_ConnectionType ) {
//       qDebug() << "  -->> trying:  " << (( SceneItem_Connection * )m_list[i] )->index.row() <<  " " <<
          (( SceneItem_Connection * )m_list[i] )->index.column();
      if (compareIndexes((( SceneItem_Connection * )m_list[i] )->index, index )) {
//         qDebug() << "connection found";
        return m_list[i];
      }
    }
  }
  qDebug() << "failed to modify the item, since the QGraphicsScene equivalent to the given QPersistentModelIndex wasn't found";
  return NULL;
}

// I hope this function in not incomplete
bool GraphicsScene::compareIndexes(const QPersistentModelIndex & a, const QPersistentModelIndex & b) {
  if (a.row() != b.row())
    return false;
  if (a.internalPointer () != b.internalPointer ())
    return false;
  return true;
}

void GraphicsScene::keyPressEvent( QKeyEvent * keyEvent ) {
  //   qDebug() << "got this event";
  // del ->> remove an item or remove selection
  if ( keyEvent->key() == Qt::Key_Delete ) {
    qDebug() << "del event";
    qDebug() << selectedItems().size();
  }
}

// void GraphicsScene::contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent ){
//   qDebug() << "event";
// }


