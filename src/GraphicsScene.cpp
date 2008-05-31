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

GraphicsScene::~GraphicsScene() {}

void GraphicsScene::selectionChanged() {
  qDebug( "Selection changed, %i selected items", selectedItems().size() );
}

QGraphicsItem* GraphicsScene::addNode( QPersistentModelIndex item ) {
//   qDebug() << "addNode( QPersistentModelIndex item )";
  SceneItem_Node* node = new SceneItem_Node( item );
  addItem( node );
  node->setPos( node->pos().x() + qrand() % 400, node->pos().y() + qrand() % 600 );
  modifyNode( node );
  return node;
}

QGraphicsItem* GraphicsScene::addConnection( QPersistentModelIndex item ) {
  qDebug() << "addConnection( QPersistentModelIndex item )";
  SceneItem_Connection * cItem = new SceneItem_Connection( item );
  addItem( cItem );
  modifyConnection( cItem );
  return cItem;
}

void GraphicsScene::modifyNode( QPersistentModelIndex item ) {
  modifyNode( modelToSceenIndex( item ) );
}

void GraphicsScene::modifyNode( QGraphicsItem* item ) {
  qDebug() << "modifyNode( QGraphicsItem* item )";
  if ( item == NULL ) {
    qDebug() << "Warning, something is going wrong";
    return;
  }
  (( SceneItem_Node * )item )->updateData();
}

void GraphicsScene::modifyConnection( QPersistentModelIndex item ) {
  modifyConnection( modelToSceenIndex( item ) );
}

void GraphicsScene::modifyConnection( QGraphicsItem* item ) {
  qDebug() << "modifyConnection( QGraphicsItem* item )";
  if ( item == NULL ) {
    qDebug() << "Warning, something is going wrong";
    return;
  }
  (( SceneItem_Connection * )item )->updateData();
}

void GraphicsScene::reset() {
  // FIXME not implemented yet
  qDebug() << "FIXME should call reset() in the GraphicsScene now";
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
      if ( compareIndexes((( SceneItem_Node * )m_list[i] )->index, index ) ) {
//         qDebug() << "node found";
        return m_list[i];
      }
    }
    if ( m_list[i]->type() == SceneItem_ConnectionType ) {
//       qDebug() << "  -->> trying:  " << (( SceneItem_Connection * )m_list[i] )->index.row() <<  " " <<
      (( SceneItem_Connection * )m_list[i] )->index.column();
      if ( compareIndexes((( SceneItem_Connection * )m_list[i] )->index, index ) ) {
//         qDebug() << "connection found";
        return m_list[i];
      }
    }
  }
  qDebug() << "failed to modify the item, since the QGraphicsScene equivalent to the given QPersistentModelIndex wasn't found";
  return NULL;
}

// I hope this function in not incomplete
bool GraphicsScene::compareIndexes( const QPersistentModelIndex & a, const QPersistentModelIndex & b ) {
  if ( a.row() != b.row() )
    return false;
  if ( a.internalPointer() != b.internalPointer() )
    return false;
  return true;
}

void GraphicsScene::keyPressEvent( QKeyEvent * keyEvent ) {
  if ( keyEvent->key() == Qt::Key_X ) {
    removeEvent();
  }
  if ( keyEvent->key() == Qt::Key_P ) {
    print();
  }
  if ( keyEvent->key() == Qt::Key_Escape ) {
    emit hideView();
  }
  if ( keyEvent->key() == Qt::Key_N ) {
    qDebug() << "adding a new node";
  }
  if ( keyEvent->key() == Qt::Key_C ) {
    qDebug() << "FIXME adding a new connection";
  }
  if ( keyEvent->key() == Qt::Key_Plus ) {
    qDebug() << "FIXME zoom in";
  }
  if ( keyEvent->key() == Qt::Key_Minus ) {
    qDebug() << "FIXME zoom out";
  }
  if ( keyEvent->key() == Qt::Key_G ) {
    qDebug() << "FIXME enable/disable grid";
  }

  if ( keyEvent->key() == Qt::Key_A && keyEvent->modifiers() == Qt::ControlModifier ) {
    qDebug() << "FIXME select all items in the scene";
//     items();
  }
  // node start toggle
  if ( keyEvent->key() == Qt::Key_S ) {
    qDebug() << "FIXME on mouseOver Node, trigger: start toggle";
    startToggleEvent( customRole::StartRole );
  }
  // node final toggle
  if ( keyEvent->key() == Qt::Key_F ) {
    qDebug() << "FIXME on mouseOver Node, trigger: final toggle";
    startToggleEvent( customRole::FinalRole );
  }
}

void GraphicsScene::startToggleEvent( int role ) {
  if ( selectedItems().size() == 1 ) {
    QGraphicsItem* item = selectedItems().first();
    if ( item->type() == SceneItem_NodeType ) {
      QPersistentModelIndex index = (( SceneItem_Node* )item )->index;
      bool state = model->data( index, role ).toBool();
      model->setData( index, !state, role );
    } else {
      qDebug() << "select a node to use this toggle";
    }
  } else {
    qDebug() << "select only one item to use the toggle";
  }
}

// void GraphicsScene::contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent ){
//   qDebug() << "event";
// }

void GraphicsScene::print() {
  qDebug() << "printing";
  QPrinter printer;
  if ( QPrintDialog( &printer ).exec() == QDialog::Accepted ) {
    QPainter painter( &printer );
    painter.setRenderHint( QPainter::Antialiasing );
    render( &painter );
  }
}

void GraphicsScene::removeNode( QPersistentModelIndex item ) {
  QGraphicsItem* gItem = modelToSceenIndex( item );
  if ( gItem == NULL ) {
    qDebug() << "FATAL ERROR: gItem was NULL" << __FILE__ << ", " << __LINE__ << ", " << __FUNCTION__;
    exit( 0 );
  }
  removeItem( gItem );
}

void GraphicsScene::removeConnection( QPersistentModelIndex item ) {
  QGraphicsItem* gItem = modelToSceenIndex( item );
  if ( gItem == NULL ) {
    qDebug() << "FATAL ERROR: gItem was NULL" << __FILE__ << ", " << __LINE__ << ", " << __FUNCTION__;
    exit( 0 );
  }
  removeItem( gItem );
}

void GraphicsScene::removeEvent() {
  qDebug() << "removeEvent";
  qDebug() << selectedItems().size();
  foreach( QGraphicsItem* z, selectedItems() ) {
    if ( z->type() == SceneItem_ConnectionType ) {
      model->removeConnection((( SceneItem_Connection * )z )->index );
    }
    if ( z->type() == SceneItem_NodeType ) {
      model->removeNode((( SceneItem_Node * )z )->index );
    }
  }
}

/// this wrapper function is here to enable all QGraphicsItems to query for data
/// this is handy since all important querying can now be done from within the item,
/// and creates true object encapsulation
QVariant GraphicsScene::data( const QModelIndex &index, int role ) const {
  return model->data( index, role );
}


