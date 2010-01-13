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

#ifndef SCENEITEM_CONNECTION_H
#define SCENEITEM_CONNECTION_H

#include <QGraphicsItem>
#include <QPersistentModelIndex>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QRectF>
#include <QPainterPath>
#include <QtGui>
#include <math.h>

#include "SceneItem_Node.h"
#include "SceneItem_Types.h"
#include "SceneItem_ConnectionHandle.h"

#define CIRCLE_FOR_SYNBOL_RADIUS 14
#define MAX_BRUSH_SIZE 32
#define LOOP_INIT_POSITION_X 0
#define LOOP_INIT_POSITION_Y 60

class SceneItem_Node;
class SceneItem_ConnectionHandle;

/*! represents a connection item in the graphicsScene: normal connection and loop
problems: this class should be split into one base class with general purpose functions and two
 ** inheriting classes normal_connection and loop_connection to make a lot of things clearer */
class SceneItem_Connection : public QGraphicsItem {
    friend class SceneItem_ConnectionHandle;
  public:
    /*! constructor which binds the index for lifetime */
    SceneItem_Connection( QPersistentModelIndex index );
    /*! ensure that you delete all connections first and then all nodes */
    ~SceneItem_Connection();
    /*! this code does:
     **  - track destination changes of a connection
     **  - updates the toolTipLabel for on mouse over
     **  - decides if a item is:
     **    - shown (connection/loop)
     **    - hidden (uninitalized connection)
     **
     ** Variable a and b are used as well as myStartItem/myEndItem to find out
     ** if the connection changed since one can alter the destination of it.
     */
    void updateData();
    /*! srcNode or dstNode pos changed, we need to relayout & update the connection */
    void updatePosition();
    /*! this changes the labelItem position. the labelItem is used to display the label of a connection */
    void updateLabelPosition();
    /*! callback function called when the ConnectionHandle (called labelItem) is moved:
    ** normal connection (no loop):
    **  - basically this math inverts void SceneItem_Connection::updateLabel() functionality
    ** loop connection:
    **  - the position of a loop item is fixed but this could be changed */
    void labelItemPositionChangeCallback( const QPointF& oldPos, const QPointF& newPos );
    /*! holds the dimensions of the connection. the dimension can change and then
    ** prepareGeometryChange(); has to be called. the dimension is influenced by:
    ** - the startnode and endnode position.
    ** - by the bezier dimensions if used (currently not used but still there)
    ** - labelItem position*/
    QRectF boundingRect() const;
    /*! resets the customTransformation position of a loop's itemLabel */
    void resetLoopPosition();
    /*! the startItem can't be changed once set */
    SceneItem_Node *startItem() const {
      return myStartItem;
    }
    /*! the enditem can be changed but if the enditem is deleted the connection pointing
    ** to it is deleted implicitly*/
    SceneItem_Node *endItem() const {
      return myEndItem;
    }
    /*! used to identify this object type */
    int type() const;
    /*! when this object should be highlighted (drawn in a different way) */
    void highlight( bool status );
    /*! there is an autolayout function which can be disabled. this autolayout does a nice job
    ** when adding the n'th connection between two nodes since they won't overlap */
    bool customTransformation();
    /*! checks if myStartItem == myEndItem*/
    bool isLoop();
    /*! this factor is used for the autoLayout which is set from either of the connected nodes */
    void setAutoLayoutFactor( qreal factor );
    /*! enabled the autoLayout algorithm of a node to layout this loop item */
    void setLoopPosition(QPointF newPos);
    /*! this index is set from the constructor and bound for lifetime */
    QPersistentModelIndex index;
  protected:
    /*! see customTransformation */
    void setCustomTransformation( bool value );
    /*! see the Qt docs about QGraphicsItem */
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
    /*! see the Qt docs about QGraphicsItem */
    QPainterPath shape() const;
    /*! when this object should be highlighted (drawn in a different way) */
    bool m_highlight;
  private:
    /*! this creates a custom path. could be cached to optmize the item drawing. on geometry changes
    ** this path changes implicitly. does some computations for bezier stuff which isn't used right
    ** now but still isn't removed. */
    QPainterPath connectionPath() const;
    /*! used to track mouseOver for item highlighting */
    void hoverEnterEvent( QGraphicsSceneHoverEvent * event );
    /*! used to track mouseOver for item highlighting */
    void hoverLeaveEvent( QGraphicsSceneHoverEvent * event );
    /*! creates a line between a and b but both sides are cut off by the radius of a node so that
    ** the line is shorter. needed for proper drawing of the arrow head */
    QLineF createLine( QPointF a, QPointF b );
    /*! used to set a custom color for drawing of the connection */
    void setColor( const QColor &color ) {
      myColor = color;
    }
    /*! internal customTransformation variable */
    bool m_customTransformation;
    /*! orthogonal offset has it's special function for:
    **  a virtual line between the two nodes is used to place the labelItem. But if the labelItem is
    **  moved we have to find out how much it is moved relative to this intermediate point. we track
    **  the offset on the line: poffset and the offset which is orthogonal to the line ooffset */
    qreal ooffset;
    /*! orthogonal offset has it's special function for:
     **  a virtual line between the two nodes is used to place the labelItem. But if the labelItem is
     **  moved we have to find out how much it is moved relative to this intermediate point. we track
     **  the offset on the line: poffset and the offset which is orthogonal to the line ooffset */
    qreal poffset;
    /*! holds the position of the labelItem if this connection is a loop unused in all other cases*/
    QPointF loopPosition;
    /*! used for drawing the arrowHead (still no caching here) */
    QPolygonF arrowHead;
    /*! ... */
    QPen pen;
    /*! private variable which holds the color, use setColor to set it later */
    QColor m_color;
    /*! private variable which holds the color, use setColor to set it later */
    QColor myColor;
    /*! returns the QGraphicsItem* of the start node */
    SceneItem_Node *myStartItem;
    /*! returns the QGraphicsItem* of the end node  */
    SceneItem_Node *myEndItem;
    /*! this line item is used to compute the ooffset/poffset */
    QLineF line;
    /*! this item is used to display the label 'on' the connection. it is also used as editor or to
    ** move the way the connection is drawn. */
    SceneItem_ConnectionHandle* labelItem;
};

#endif
