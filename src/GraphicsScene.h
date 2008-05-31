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

#include <QPrinter>
#include <QPrintDialog>

#include "Model.h"
#include "SceneItem_Node.h"
#include "SceneItem_Connection.h"

/**
 @author Joachim Schiele <js@lastlog.de>
*/
class GraphicsScene : public QGraphicsScene {
    Q_OBJECT
  public:
    GraphicsScene( Model *model );
    ~GraphicsScene();
  public slots:
    QGraphicsItem* addNode( QPersistentModelIndex item );
    QGraphicsItem* addConnection( QPersistentModelIndex item );
    void modifyNode( QPersistentModelIndex item );
    void modifyConnection( QPersistentModelIndex item );
    void removeNode( QPersistentModelIndex item );
    void removeConnection( QPersistentModelIndex item );
    void reset();
//   private slots: FIXME
    void selectionChanged();
//   protected: FIXME
    QVariant data( const QModelIndex &index, int role ) const;

  // private: FIXME
    QGraphicsItem* modelToSceenIndex( QPersistentModelIndex index );
  private:
    Model *model;
    void keyPressEvent( QKeyEvent * keyEvent );
    void modifyNode( QGraphicsItem* item );
    void modifyConnection( QGraphicsItem* item );
    void removeEvent();
    bool compareIndexes( const QPersistentModelIndex & a, const QPersistentModelIndex & b );
    void startToggleEvent(int role);

//     void contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent );
    void print();
  signals:
    void hideView();
};

#endif
