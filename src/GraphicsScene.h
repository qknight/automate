//
// C++ Interface: GraphicsScene
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QPersistentModelIndex>
#include <QGraphicsTextItem>
#include <QVariant>
#include <QDebug>
#include <QKeyEvent>

#include "Model.h"
#include "SceneItem_Node.h"
#include "SceneItem_Connection.h"

/**
 @author Joachim Schiele <js@lastlog.de>
*/
class GraphicsScene : public QGraphicsScene {
  public:
    GraphicsScene(Model *model);
    ~GraphicsScene();
  public slots:
    void selectionChanged();
  public:
    void addNode( QPersistentModelIndex item );
    void addConnection( QPersistentModelIndex item );
    void modifyNode(QPersistentModelIndex item);
    void modifyConnection(QPersistentModelIndex item);
    // maybe we want to remove an item
//     void removeNode( QGraphicsItem* item );
//     void removeConnection( QGraphicsItem* item );
    void reset();
    void keyPressEvent ( QKeyEvent * keyEvent );
  private:
    bool compareIndexes(const QPersistentModelIndex & a, const QPersistentModelIndex & b);
    Model *model;
    QGraphicsItem* modelToSceenIndex(QPersistentModelIndex index);
//     void contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent );
};

#endif
