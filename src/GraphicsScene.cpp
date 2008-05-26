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
  int id = model->data( item, customRole::IdRole ).toInt();
  QGraphicsItem* a = modelToSceenIndex( QPersistentModelIndex( model->parent( item ) ) );
  QModelIndex next_node_index = model->next_nodeModelIndex( item );
  if ( !next_node_index.isValid() ) {
    qDebug() << "Critical error because next_node isn't a valid index";
  }
  QGraphicsItem* b = modelToSceenIndex( next_node_index );
  int symbol_index = model->data(item, customRole::IndexRole).toInt();
  SceneItem_Connection * cItem = new SceneItem_Connection( item, symbol_index, ( SceneItem_Node * )a, ( SceneItem_Node * )b );
  cItem->setData( 0, &item );
  (( SceneItem_Node * )a )->addConnection( cItem );
  (( SceneItem_Node * )b )->addConnection( cItem );
  addItem( cItem );
}

void GraphicsScene::reset() {
  qDebug() << "should call reset() in the GraphicsScene now";
}

/*
** the qgraphicsscene stores all graphical objects and in those objects
** we have a QPersistentModelIndex stored. this gives us the possibility of
** having several different graphicsViews on the same automate
*/
QGraphicsItem* GraphicsScene::modelToSceenIndex( QPersistentModelIndex index ) {
  QList<QGraphicsItem *> m_list = items();
  for ( int i = 0; i < m_list.size(); ++i ) {
    if ( (( SceneItem_Node * )m_list[i])->type() == SceneItem_NodeType ) {
      if ( (( SceneItem_Node * )m_list[i])->index == index )
        return m_list[i];
    }
  }
  return NULL;
}

void GraphicsScene::keyPressEvent ( QKeyEvent * keyEvent ){
//   qDebug() << "got this event";
  // del ->> remove an item or remove selection
  if (keyEvent->key() == Qt::Key_Delete) {
    qDebug() << "del event";
    qDebug() << selectedItems().size();
  }
}

