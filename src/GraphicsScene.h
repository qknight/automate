// automate implements an automate class in c++ using qt4
// Copyright (C) 2007 Joachim Schiele
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// version 3 as published by the Free Software Foundation
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

/**
  @author Joachim Schiele <js@lastlog.de>
*/

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
/*! */
class GraphicsScene : public QGraphicsScene {
  Q_OBJECT
  friend class SceneItem_Node;
  friend class SceneItem_Connection;
  friend class SceneItem_ConnectionHandle;
  friend class ItemView;

  public:
    /*! constructor */
    GraphicsScene( Model *model );
    /*! destructor */
    ~GraphicsScene();
    /*! if connection should be highlighted on mouse over */
    bool want_highlight();
    /*! if connections or nodes should show their bbox, helpful for debugging */
    bool want_boundingBox();
    /*! the shape of an item is it's area on which you can click to select the item, helpful for debugging  */
    bool want_drawItemShape();
    /*! colors the connecions, think what you want about it */
    bool want_coloredConnectionHelper();
    /*! overwrite for custom node labels, you can label your node with 'ff' for example */
    bool want_customNodeLabels();
    /*! same as for custom node labels */
    bool want_customConnectionLabels();
    /*! a wrapper function for all items in the scene, so that they can call data() directly */
    QVariant data( const QModelIndex &index, int role ) const;
    /*! a wrapper function for all items in the scene, so that they can call setData() directly */
    bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
  protected:
    /*! callback function which is called from the Model->ItemView->GraphicsScene to notify about new node(s) */
    QGraphicsItem* nodeInserted( QPersistentModelIndex item );
    /*! callback function which is called from the Model->ItemView->GraphicsScene to notify about new connection(s) */
    QGraphicsItem* connectionInserted( QPersistentModelIndex item );
    /*! callback function which is called from the Model->ItemView->GraphicsScene to notify about changed node(s) */
    void updateNode( QPersistentModelIndex item );
    /*! callback function which is called from the Model->ItemView->GraphicsScene to notify about changed connection(s) */
    void updateConnection( QPersistentModelIndex item );
    /*! callback function which is called from the Model->ItemView->GraphicsScene to notify about nodes which are about to be deleted node(s) */
    bool nodeRemoved( QPersistentModelIndex item );
    /*! callback function which is called from the Model->ItemView->GraphicsScene to notify about connections which are about to be deleted connections(s) */
    bool connectionRemoved( QPersistentModelIndex item );
  private:
    /*! internal variable */
    bool m_want_highlight;
    /*! internal variable  */
    bool m_want_boundingBox;
    /*! internal variable */
    bool m_want_drawItemShape;
    /*! internal variable */
    bool m_want_coloredConnectionHelper;
    /*! internal variable */
    bool m_want_customNodeLabels;
    /*! internal variable */
    bool m_want_customConnectionLabels;
    /*! converts a QPersistentModelIndex into a QGraphicsItem */
    QGraphicsItem* modelToSceenIndex( QPersistentModelIndex index );
    /*! this (red) line is needed for adding connections with the MMB (mid-mouse-button) between nodes */
    QGraphicsLineItem *line;
    /*! the GraphicsScene visualizes the data of this model */
    Model *model;
    /*! we handle all keyboard events here, this is only interrupted when an item got focus */
    void keyPressEvent( QKeyEvent * keyEvent );
    /*! we handle all mouse events here, this is only interrupted when an item got focus */
    void mousePressEvent( QGraphicsSceneMouseEvent * event );
    /*! we handle all mouse events here, this is only interrupted when an item got focus */
    void mouseMoveEvent( QGraphicsSceneMouseEvent * event );
    /*! we handle all mouse events here, this is only interrupted when an item got focus */
    void mouseReleaseEvent( QGraphicsSceneMouseEvent * event );
    /*! updates a node based on item pointer */
    void updateNode( QGraphicsItem* item );
    /*! updates a connection based on item pointer*/
    void updateConnection( QGraphicsItem* item );
    /*! a custom compare function to only compare fields in a QPersistentModelIndex which matter since
    ** the treeView handles rows/columns in items the GraphicsScene doesn't so we do not need to
    ** compare all the fields */
    bool compareIndexes( const QPersistentModelIndex & a, const QPersistentModelIndex & b );
  public slots:
    /*! when a user want's to add a node we need to call this function which will request a node on the model side*/
    void insertNode();
  protected slots:
    /*! abstract version of (for example) toggleFinalEvent */
    void toggleEvent( int role );
    /*! switches the final state in the currently selected QGraphicsItem which is a node */
    void toggleFinalEvent();
    /*! switches the start state in the currently selected QGraphicsItem which is a node */
    void toggleStartEvent();
    /*! remove a selection of items, can be nodes or connections */
    void removeEvent(unsigned int removalMode);
    /*! removes only a single element out of a selection, not called directly */
    void removeEvent();
    /*! create a pdf based on the QGraphicsScene content */
    void print();
    /*! see want_boundingBox */
    void toggleBoundingBox();
    /*! see want_drawItemShape */
    void toggleDrawItemShape();
    /*! see want_coloredConnectionHelper */
    void toggle_coloredConnectionHelper();
    /*! see want_customConnectionLabels */
    void toggle_customConnectionLabels();
    /*! see want_customNodeLabels */
    void toggle_customNodeLabels();
    /*! this is similar to clear() in qt 4.4 but as we need to remove all connections
    ** and then all nodes this is the way we go*/
    void clearScene();
  private slots:
    /*! the current selection of items changes, for example when some nodes or
    connections vanished based on a model request since another view deleted them */
    void selectionChanged();
    /*! see want_highlight */
    void toggleHighlight();
  signals:
    /*! hides this view widget */
    void hideView();
    /*! helper signal, see code */
    void toggleRenderHints();
    /*! helper signal, see code */
    void zoomOut();
    /*! helper signal, see code */
    void zoomIn();
    /*! helper signal, see code */
    void zoomFit();
    /*! when a new view pops up this reset() is called to query items from the model */
    void reset();
};

#endif
