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
  m_want_highlight = false;
  m_want_boundingBox = false;
  m_want_drawItemShape = false;
  m_want_coloredConnectionHelper = false;
  m_want_customNodeLabels = true;
  m_want_customConnectionLabels = false;
  line = 0;
  connect( this, SIGNAL( selectionChanged() ), this, SLOT( selectionChanged() ) );

  //FIXME qt 4.4.x and 4.3.x have a bug in the BspTreeIndex methods -> removeItem(QGraphicsItem)
  //      since in some cases an already deleted item is queried which segfaults the program
  //      POSSIBLE CAUSE: maybe this isn't a bug in qt BUT in my QGraphicsItem implementation's
  //      boundingBox on item resize, have to track that done yet.
  //      FINAL SOLUTION: found it, it was my own SceneItem_Connection item's wrong dimension
  // //   QRectF SceneItem_Connection::boundingRect() const {
  // //   QRectF z = QRectF(-2000,-2000,4000,4000);
  // //   return z;
  //      finally showed that with that dimension it would never crash -> now i have to fix that...

  setItemIndexMethod(NoIndex);
}

GraphicsScene::~GraphicsScene() {
//   qDebug() << __FUNCTION__;
  clearScene();
}

void GraphicsScene::selectionChanged() {
//   qDebug( "Selection changed, %i selected items", selectedItems().size() );
}

QGraphicsItem* GraphicsScene::nodeInserted( QPersistentModelIndex item ) {
//   qDebug() << __FUNCTION__;
  SceneItem_Node* node = new SceneItem_Node( item );
  addItem( node );
  // FIXME need to implement this!
  // when the ItemView widget has focus &http://wiki.openmoko.org/wiki/OpenMoko_under_QEMU& when the mouse is in the ItemView
  //   only then insert the new node below the cursor
  // else put it at an random position near QPoint(0,0)
  node->setPos( node->pos().x() + qrand() % 600, node->pos().y() + qrand() % 400 );
  updateNode( node );
  return node;
}

QGraphicsItem* GraphicsScene::connectionInserted( QPersistentModelIndex item ) {
//   qDebug() << __FUNCTION__;
  SceneItem_Connection * cItem = new SceneItem_Connection( item );
  addItem( cItem );
  updateConnection( cItem );
  return cItem;
}

void GraphicsScene::updateNode( QPersistentModelIndex item ) {
  updateNode( modelToSceenIndex( item ) );
}

void GraphicsScene::updateNode( QGraphicsItem* item ) {
//   qDebug() << "updateNode( QGraphicsItem* item )";
  if ( item == NULL ) {
    qDebug() << __FUNCTION__ << " " << __LINE__ << "Warning, something is going wrong";
    return;
  }
  (( SceneItem_Node * )item )->updateData();
}

void GraphicsScene::updateConnection( QPersistentModelIndex item ) {
  updateConnection( modelToSceenIndex( item ) );
}

void GraphicsScene::updateConnection( QGraphicsItem* item ) {
//   qDebug() << "updateConnection( QGraphicsItem* item )";
  if ( item == NULL ) {
    qDebug() << __FUNCTION__ << " " << __LINE__ << " Warning, something is going wrong";
    return;
  }
  (( SceneItem_Connection * )item )->updateData();
}

/*
** in qt 4.4 we have clear() as well but we won't use it since we have to
** remove all connections first and then all nodes. removing a node while it still
** has references (in/out connections) will result in a error since we need to
** have that error for debugging of other data-structure errors.
**
** behaviour can be changed later if appreciated
*/
void GraphicsScene::clearScene() {
//   qDebug() << __FUNCTION__;
//   foreach( QGraphicsItem* i, items() ) {
//     QString o;
//     switch(i->type()) {
//       case  SceneItem_NodeType:
//         o="SceneItem_NodeType";
//         break;
//       case  SceneItem_ConnectionType:
//         o="SceneItem_ConnectionType";
//         break;
//       case  SceneItem_ConnectionHandleType:
//         o="SceneItem_ConnectionHandleType";
//         break;
//       case  SceneItem_LabelEditorType:
//         o="SceneItem_LabelEditorType";
//         break;
//     }
//     qDebug() << "item: " << (unsigned int)i << " type::" << o;
//   }

  QVector<QGraphicsItem*> connections;
  QVector<QGraphicsItem*> nodes;
//   qDebug() << " ======= " << items().size() << " items to delete ========== ";
  foreach( QGraphicsItem* i, items() ) {
    if ( i->type() == SceneItem_ConnectionType ) {
      connections.push_back( i );
    }
    if ( i->type() == SceneItem_NodeType ) {
      nodes.push_back( i );
    }
  }
  foreach( QGraphicsItem* i, connections )
    delete i;
  foreach( QGraphicsItem* i, nodes )
    delete i;
  if ( items().size() ) {
    qDebug() << "Warning: we still got items on this scene while there should not be any!";
    sleep (10);
  }
}

/*
** the qgraphicsscene stores all graphical objects and in those objects
** we have a QPersistentModelIndex stored. this gives us the possibility of
** having several different graphicsViews on the same automate
*/

// a general compare function had to be implemented: compareIndexes
// since this implementation doesn't use
// column BUT columns somehow whxere reported to be different, meaning: a stored index could have column 3
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
  qDebug() << "sleeping 10 seconds now";
  sleep(10);
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
  //FIXME replace this code with QShortCut/QAction
  if ( focusItem() != NULL ) {
    QGraphicsScene::keyPressEvent( keyEvent );
    return;
  }
  if ( keyEvent->key() == Qt::Key_X && keyEvent->modifiers() == Qt::ControlModifier ) {
    removeEvent(1);
  }

  if ( keyEvent->key() == Qt::Key_X && keyEvent->modifiers() != Qt::ControlModifier) {
    removeEvent(0);
  }
  if ( keyEvent->key() == Qt::Key_P ) {
    print();
  }
  if ( keyEvent->key() == Qt::Key_Escape ) {
    emit hideView();
  }
  if ( keyEvent->key() == Qt::Key_N ) {
    insertNode();
  }

  if ( keyEvent->key() == Qt::Key_B ) {
    qDebug() << "toggleBoundingBox()";
    toggleBoundingBox();
  }
  if ( keyEvent->key() == Qt::Key_L ) {
    qDebug() << "'l' - toggle_coloredConnectionHelper";
    toggle_coloredConnectionHelper();
  }

  if ( keyEvent->key() == Qt::Key_Plus ) {
    emit zoomIn();
//     qDebug() << "zoom in";
  }
  if ( keyEvent->key() == Qt::Key_Minus ) {
    emit zoomOut();
//     qDebug() << "zoom out";
  }
  if ( keyEvent->key() == Qt::Key_Slash ) {
    emit zoomFit();
  }
  if ( keyEvent->key() == Qt::Key_G ) {
    qDebug() << "NOT IMPLEMENTED YET FIXME enable/disable grid";
  }
  if ( keyEvent->key() == Qt::Key_F1 ) {
    qDebug() << "NOT IMPLEMENTED YET toggle rendering";
  }
  if ( keyEvent->key() == Qt::Key_U ) {
    update();
    qDebug() << endl << endl << endl << endl;
    qDebug() << "scene->update(): " << items().size() << " items in the scene";
  }
  if ( keyEvent->key() == Qt::Key_U && keyEvent->modifiers() == Qt::ControlModifier ) {
    emit reset();
  }

  if ( keyEvent->key() == Qt::Key_A && keyEvent->modifiers() == Qt::ControlModifier ) {
    qDebug() << "Selects all items in the scene";
    QPainterPath path;
    path.addRect( sceneRect() );
    setSelectionArea( path );
  }
  // node start toggle
  if ( keyEvent->key() == Qt::Key_S ) {
    toggleStartEvent();
  }
  // node final toggle
  if ( keyEvent->key() == Qt::Key_F ) {
    toggleFinalEvent();
  }
  if ( keyEvent->key() == Qt::Key_H ) {
    qDebug() << "toggle highlighting mode";
    toggleHighlight();
  }
  if ( keyEvent->key() == Qt::Key_E ) {
    qDebug() << "toggle shape drawing mode";
    toggleDrawItemShape();
  }

  if ( keyEvent->key() == Qt::Key_T ) {
    qDebug() << "toggle rendering mode to enable/disable antialiasing";
    emit toggleRenderHints();
  }
}

void GraphicsScene::toggleStartEvent() {
  toggleEvent( customRole::StartRole );
}

void GraphicsScene::toggleFinalEvent() {
  toggleEvent( customRole::FinalRole );
}

void GraphicsScene::toggleEvent( int role ) {
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
  qDebug() << "printing the view";
  QPrinter printer;
  if ( QPrintDialog( &printer ).exec() == QDialog::Accepted ) {
    QPainter painter( &printer );
    painter.setRenderHint( QPainter::Antialiasing );
    render( &painter );
  }
}

/*
** we can be sure that item exists
*/
bool GraphicsScene::nodeRemoved( QPersistentModelIndex item ) {
//   qDebug() << __FUNCTION__;
  QGraphicsItem* nItem = modelToSceenIndex( item );
  if ( nItem == NULL ) {
    qDebug() << "FATAL ERROR: nItem was NULL" << __FILE__ << ", " << __LINE__ << ", " << __FUNCTION__;
    // FIXME after testing this can be changed to return instaead of exit
    exit( 0 );
//     return false;
  }
//   qDebug() << "nItem is: " << QString("%1").arg((unsigned int) nItem,0,16);
  delete nItem;
  return true;
}

/*
** we can be sure that item exists
*/
bool GraphicsScene::connectionRemoved( QPersistentModelIndex item ) {
//   qDebug() << __FUNCTION__ << (unsigned int)this;
  QGraphicsItem* cItem = modelToSceenIndex( item );

  if ( cItem == NULL ) {
    qDebug() << "FATAL ERROR: cItem was NULL" << __FILE__ << ", " << __LINE__ << ", " << __FUNCTION__;
    // FIXME after testing this can be changed to return instaead of exit
    exit( 0 );
//     return false;
  }
//   qDebug() << (unsigned int)cItem->scene() << " vs " << (unsigned int) this;
//   qDebug() << QString("%1").arg((unsigned int) cItem->scene(),0,16) << " vs " << QString("%1").arg((unsigned int) this,0,16);
//   qDebug() << "cItem is: " << QString("%1").arg((unsigned int) cItem,0,16);

  delete cItem;
  return true;
}

void GraphicsScene::removeEvent() {
  removeEvent(0);
}

void GraphicsScene::removeEvent(unsigned int removalMode) {
  //FIXME, doesn't work yet
  // removalMode == 0 -> remove all connections, leave nodes
  // removalMode == 1 -> remove all nodes+connections in selectionChanged

//   qDebug() << "removeEvent, removing at least" << selectedItems().size() << " items";
  QList<QPersistentModelIndex> list;
  foreach( QGraphicsItem* z, selectedItems() ) {
    QModelIndex index;
    if ( z->type() == SceneItem_NodeType ) {
      if (removalMode == 0) {
        index = (( SceneItem_Node* )z )->index;
      }
    }
    else
      if ( z->type() == SceneItem_ConnectionType )
        index = (( SceneItem_Connection * )z )->index;
      else {
        qDebug() << "FATAL ERROR: no node nor a connection, what item type is it?";
        exit( 0 );
      }
    if (index.isValid())
      list.append( QPersistentModelIndex( index ) );
  }
  model->removeItems( list );
}

/// this wrapper function is here to enable all QGraphicsItems to query for data
/// this is handy since all important querying can now be done from within the item,
/// and creates true object encapsulation
QVariant GraphicsScene::data( const QModelIndex &index, int role ) const {
  return model->data( index, role );
}

/// this wrapper function is here to enable all QGraphicsItems to set data
bool GraphicsScene::setData( const QModelIndex & index, const QVariant & value, int role ) {
  return model->setData( index, value, role );
}

/*
** mousePressEvent,mouseReleaseEvent,mouseMoveEvent are used to graphically connect two nodes
** with each. even loops are possible just mouseRelease over the same node
*/
void GraphicsScene::mousePressEvent( QGraphicsSceneMouseEvent *mouseEvent ) {
  if ( items( mouseEvent->scenePos() ).count() && mouseEvent->button() == Qt::MidButton ) {
    QGraphicsScene::mousePressEvent( mouseEvent );
    line = new QGraphicsLineItem( QLineF( mouseEvent->scenePos(),
                                          mouseEvent->scenePos() ) );
    line->setPen( QPen( QColor( "RED" ), 2 ) );
    line->setZValue( 2000 );
    addItem( line );
  } else
    if ( mouseEvent->button() == Qt::MidButton ) {

    } else {
      QGraphicsScene::mousePressEvent( mouseEvent );
    }
}

void GraphicsScene::mouseReleaseEvent( QGraphicsSceneMouseEvent *mouseEvent ) {
  if ( line != 0 ) {
    QList<QGraphicsItem *> startItems = items( line->line().p1() );
    if ( startItems.count() && startItems.first() == line )
      startItems.removeFirst();
    QList<QGraphicsItem *> endItems = items( line->line().p2() );
    if ( endItems.count() && endItems.first() == line )
      endItems.removeFirst();

    removeItem( line );
    delete line;
    line = 0;

//     qDebug() << "removing line";
    if ( startItems.count() > 0 && endItems.count() > 0 &&
         startItems.first()->type() == SceneItem_NodeType &&
         endItems.first()->type() == SceneItem_NodeType
         /*&& startItems.first() != endItems.first()*/ ) {
      SceneItem_Node *startItem =
        qgraphicsitem_cast<SceneItem_Node *>( startItems.first() );
      SceneItem_Node *endItem =
        qgraphicsitem_cast<SceneItem_Node *>( endItems.first() );
      model->insertConnection( startItem->index, endItem->index );
//       qDebug() << "adding a conneciton";
    }
  }
  QGraphicsScene::mouseReleaseEvent( mouseEvent );
}

void GraphicsScene::mouseMoveEvent( QGraphicsSceneMouseEvent *mouseEvent ) {
  if ( line != 0 ) {
    QLineF newLine( line->line().p1(), mouseEvent->scenePos() );
    line->setLine( newLine );
  } else {
    QGraphicsScene::mouseMoveEvent( mouseEvent );
  }
}

void GraphicsScene::toggleHighlight() {
  m_want_highlight = !m_want_highlight;
}

void GraphicsScene::toggleBoundingBox() {
  m_want_boundingBox = !m_want_boundingBox;
  update();
}

bool GraphicsScene::want_highlight() {
  return m_want_highlight;
}

bool GraphicsScene::want_boundingBox() {
  return m_want_boundingBox;
}

void GraphicsScene::insertNode() {
  model->insertNode();
}

void GraphicsScene::toggleDrawItemShape() {
  m_want_drawItemShape = !m_want_drawItemShape;
  update();
}

bool GraphicsScene::want_drawItemShape() {
  return m_want_drawItemShape;
}

void GraphicsScene::toggle_coloredConnectionHelper() {
  m_want_coloredConnectionHelper = !m_want_coloredConnectionHelper;
  update();
}

bool GraphicsScene::want_coloredConnectionHelper() {
  return m_want_coloredConnectionHelper;
}

bool GraphicsScene::want_customNodeLabels() {
  return m_want_customNodeLabels;
}

void GraphicsScene::toggle_customNodeLabels() {
  m_want_customNodeLabels = !m_want_customNodeLabels;
  update();
}

bool GraphicsScene::want_customConnectionLabels() {
  return m_want_customConnectionLabels;
}

void GraphicsScene::toggle_customConnectionLabels() {
  m_want_customConnectionLabels = !m_want_customConnectionLabels;
  update();
}

