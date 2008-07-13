/****************************************************************************
**
** Copyright (C) 2007-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.0, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** In addition, as a special exception, Trolltech, as the sole copyright
** holder for Qt Designer, grants users of the Qt/Eclipse Integration
** plug-in the right for the Qt/Eclipse Integration to link to
** functionality provided by Qt Designer and its related libraries.
**
** Trolltech reserves all rights not expressly granted herein.
**
** Trolltech ASA (c) 2007
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

//
// C++ Implementation: SceneItem_Connection
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "SceneItem_Connection.h"

const qreal Pi = 3.14;

SceneItem_Connection::SceneItem_Connection( QPersistentModelIndex index ) : QGraphicsItem() {
//   qDebug() << __FUNCTION__ << (unsigned int)this;
  m_customTransformation = false;
  labelItem = new SceneItem_ConnectionHandle;
  labelItem->setParentItem( this );
  this->index = index;
  m_color = QColor( qrand() % 255, qrand() % 255, qrand() % 255, 255 );

  myStartItem = NULL;
  myEndItem = NULL;

  m_highlight = false;
  setFlag( QGraphicsItem::ItemIsSelectable, true );
  setAcceptsHoverEvents( true );

  myColor = Qt::black;
  pen = QPen( myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );
  line = QLine();

  ooffset = 0.0;
  poffset = 0.0;// this parameter means: -1 source node, 0.5 between mid and destnode, 1 destnode
}

// - connection is removed -> remove the reference from the two associated nodes
SceneItem_Connection::~SceneItem_Connection() {
//   qDebug() << __FUNCTION__ << "BEGIN" << (unsigned int)this;

  if (myEndItem != NULL)
    if (!myEndItem->removeConnection(this))
      qDebug() << "Connection wasn't removed propperly @ myEndItem";
  if (myStartItem != NULL && myStartItem != myEndItem)
    if (!myStartItem->removeConnection(this))
      qDebug() << "Connection wasn't removed propperly @ myStartItem";

  if (myStartItem != NULL)
    ((SceneItem_Node *)myStartItem)->layoutChange();
  if (myEndItem != NULL)
    ((SceneItem_Node *)myEndItem)->layoutChange();

  delete labelItem;
//   labelItem->deleteLater();
}

/*
** tracks destination changes of a connection (reference of a connection updates)
** updates the toolTipLabel for on mouse over
** tracks source and dest QModelIndex and QGraphicsItem
*/
void SceneItem_Connection::updateData() {
//   qDebug() << __FUNCTION__ << (unsigned int)this;
  if ( scene() == NULL ) {
    qDebug() << "item isn't in any scene, can't query for valid data";
    return;
  }
  bool forceLayoutUpdate=false;

  unsigned int id = (( GraphicsScene* )scene() )->data( index, customRole::IdRole ).toInt();
  QString toolTip = QString( "c%1" ).arg( id );
  setToolTip( toolTip );

  prepareGeometryChange();

  QString symbol = (( GraphicsScene* )scene() )->data( index, customRole::SymbolIndexRole ).toString();
  labelItem->setLabel( symbol );

  QGraphicsItem* a = (( GraphicsScene* )scene() )->modelToSceenIndex( QPersistentModelIndex( index.parent() ) );
  if ( a == NULL )
    return;
  QModelIndex next_node_index = (( Model* )index.model() )->next_nodeModelIndex( index );
  if ( !next_node_index.isValid() ) {
    qDebug() << "Critical error because next_node isn't a valid index";
    qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
    return;
  }
  QGraphicsItem* b = (( GraphicsScene* )scene() )->modelToSceenIndex( next_node_index );
  if ( b == NULL )
    return;

  // - a new connection is made (usual case)
  SceneItem_Node *s = ( SceneItem_Node * )a;
  SceneItem_Node *e = ( SceneItem_Node * )b;
  s->addConnection( this );

  if (myStartItem == NULL || myEndItem == NULL || myEndItem != e)
    forceLayoutUpdate=true;

  myStartItem = s;

  // Note: all connections which are just added are loops, once the connection
  //       is in all views it's modified and updates via updateConnection
  //       -> in case the destnode is changed, we need to remove the old reference
  //          which can either be a loop or if the treeView was used to alter the
  //          destination we can redirect a connection as well
  //
  if (myEndItem != NULL && myEndItem != e && myStartItem != myEndItem ) {
//     qDebug() << " ----> e" << (unsigned int)e;
//     qDebug() << " ----> myEndItem" << (unsigned int)myEndItem;
    myEndItem->removeConnection(this);
    e->addConnection( this );
  }

  myEndItem = e;

  if (s != e) {
//     qDebug() << "adding connection to new endItem";
    myEndItem->addConnection( this );
  }

//   qDebug() << "id of changed item " << ((GraphicsScene*)scene())->data( index, customRole::IdRole ).toInt();
  line = createLine( mapFromItem( myStartItem, 0, 0 ), mapFromItem( myEndItem, 0, 0 ) );
  updateLabelPosition();

  // create a new layout since connections have changed
  if (forceLayoutUpdate)
    s->layoutChange();

//   qDebug() << "myStartItem" << (unsigned int)myStartItem;
//   qDebug() << "myEndItem" << (unsigned int)myEndItem;

  // redraw the Connection
  update();
}

void SceneItem_Connection::updateLabelPosition() {
//   qDebug() << __FUNCTION__ << (unsigned int)this;
  // FIXME this is a hack not to deform the whole scene but should be handled BETTER!
  if ( myStartItem->collidesWithItem( myEndItem ) )
    return;

  QPointF vpos = myStartItem->pos() / 2.0 + myEndItem->pos() / 2.0;
  QLineF parallel_unitLine = line.unitVector();

  // this offset is relative: we need to recompute the relations
  qreal parallel_halfsize = line.length() / 2.0 * poffset;
  QPointF parallel_unitVector = parallel_unitLine.p2() - parallel_unitLine.p1();
  QPointF parallel_diffVector = QPointF( parallel_unitVector.x() * parallel_halfsize,
                                         parallel_unitVector.y() * parallel_halfsize );

  // this offset is absolute: we don't resize this dimension on node move
  QLineF orthogonal_normalUnitLine = parallel_unitLine.normalVector();
  QPointF orthogonal_normalUnitVector = orthogonal_normalUnitLine.p2() - orthogonal_normalUnitLine.p1();
  QPointF orthogonal_diffVector = QPointF( ooffset * orthogonal_normalUnitVector.x(),
                                  ooffset * orthogonal_normalUnitVector.y() );

  labelItem->setPos( vpos + orthogonal_diffVector + parallel_diffVector );
}

// callback function from a ConnectionLabel item
// basically this math inverts void SceneItem_Connection::updateLabel() functionality
void SceneItem_Connection::labelItemPositionCallback( const QPointF& /*oldPos*/, const QPointF& newPos ) {
  // FIXME this is a hack not to deform the whole scene and should be handled BETTER!
//   qDebug() << __FUNCTION__ << (unsigned int)this;
  if ( myStartItem->collidesWithItem( myEndItem ) )
    return;
  prepareGeometryChange();
  QPointF vpos = myStartItem->pos() / 2.0 + myEndItem->pos() / 2.0;

  QLineF parallel_unitLine = line.unitVector();
  QPointF parallel_unitVector = parallel_unitLine.p2() - parallel_unitLine.p1();
  QLineF orthogonal_normalUnitLine = parallel_unitLine.normalVector();
  QPointF orthogonal_normalUnitVector = orthogonal_normalUnitLine.p2() - orthogonal_normalUnitLine.p1();

  // 1. solve a linear equation
  // http://en.wikipedia.org/wiki/Cramer's_rule
  QPointF labelOffsetVector = vpos - newPos;

// we need to find the two factors of our two unitComponents used to generate labelOffsetVector
// Equation:
//   parallel_unitVector*x +  orthogonal_normalUnitVector*y = labelOffsetVector;

  qreal det = parallel_unitVector.x() * orthogonal_normalUnitVector.y() -
              parallel_unitVector.y() * orthogonal_normalUnitVector.x();
  qreal x = ( labelOffsetVector.x() * orthogonal_normalUnitVector.y() -
              orthogonal_normalUnitVector.x() * labelOffsetVector.y() )
            / det;

  qreal y = ( parallel_unitVector.x() * labelOffsetVector.y() -
              labelOffsetVector.x() * parallel_unitVector.y() )
            / det;
  ooffset = -y;

  // 2. translate the parallel offset into the paramter we need
  poffset = -x / ( line.length() / 2 );

  // 3. finally update what we see
  update();
}

void SceneItem_Connection::updatePosition() {
//   qDebug() << __FUNCTION__ << (unsigned int)this;
  prepareGeometryChange();
  line = createLine( mapFromItem( myStartItem, 0, 0 ), mapFromItem( myEndItem, 0, 0 ) );
  updateLabelPosition();
  update();
}

QLineF SceneItem_Connection::createLine( QPointF a, QPointF b ) {
//   qDebug() << __FUNCTION__ << (unsigned int)this;
  if ( myStartItem->collidesWithItem( myEndItem ) )
    return QLineF();

  QLineF tLine( a, b );

  int radius = 25; // radius of the circle for an node item
  float length = tLine.length();

  if ( length < 2 * radius ) {
    return QLineF();
  }
  float n = length / ( radius + 4 );
  QLineF l = QLineF( tLine.pointAt( 1 / n ), tLine.pointAt( 1 - 1 / n ) );
  return l;
}

QRectF SceneItem_Connection::boundingRect() const {
//   QRectF z = QRectF(-2000,-2000,4000,4000);
//   return z;
  QRectF bbox = connectionPath().boundingRect();
  return bbox.adjusted( -MAX_BRUSH_SIZE, -MAX_BRUSH_SIZE, MAX_BRUSH_SIZE, MAX_BRUSH_SIZE );
}

QPainterPath SceneItem_Connection::shape() const {
//   qDebug() << __FUNCTION__ << (unsigned int)this;
#define CLICKABLERANGE 12
  QPainterPathStroker s;
  s.setWidth( CLICKABLERANGE );
  QPainterPath p = connectionPath();
  QPainterPath path = s.createStroke( p );
  return path;
}

QPainterPath SceneItem_Connection::connectionPath() const {
//   qDebug() << __FUNCTION__ << (unsigned int)this;
  // FIXME this is a hack not to deform the whole scene and should be handled BETTER!
  if ( myStartItem == NULL || myEndItem == NULL )
    return QPainterPath();
  if ( myStartItem->collidesWithItem( myEndItem ) )
    return QPainterPath();
  // this fixed another issue...
  if (line.length() == 0)
    return QPainterPath();

  // REDUNDANT CODE BELOW
  QPointF vpos = myStartItem->pos() / 2.0 + myEndItem->pos() / 2.0;
  QLineF parallel_unitLine = line.unitVector();

  // this offset is relative: we need to recompute the relations
  qreal parallel_halfsize = line.length() / 2.0 * poffset;
  QPointF parallel_unitVector = parallel_unitLine.p2() - parallel_unitLine.p1();
  QPointF parallel_diffVector = QPointF( parallel_unitVector.x() * parallel_halfsize,
                                         parallel_unitVector.y() * parallel_halfsize );

  // this offset is absolute: we don't resize this dimension on node move
  QLineF orthogonal_normalUnitLine = parallel_unitLine.normalVector();
  QPointF orthogonal_normalUnitVector = orthogonal_normalUnitLine.p2() - orthogonal_normalUnitLine.p1();
  QPointF orthogonal_diffVector = QPointF( ooffset * orthogonal_normalUnitVector.x(),
                                  ooffset * orthogonal_normalUnitVector.y() );
  // REDUNDANT CODE ABOVE

  QPainterPath path( mapFromItem( myStartItem, 0, 0 ) );
  QPointF offset = orthogonal_diffVector / 2;
  qreal f = ( line.length() / 2 + poffset ) / 2;
  qreal v = ( line.length() / 2 - poffset ) / 2;

  QPointF a1 = /*offset +*/ mapFromItem( myStartItem, 0, 0 );
  QPointF a2 = parallel_unitVector * f + orthogonal_diffVector + mapFromItem( myStartItem, 0, 0 );
  path.cubicTo( a1, a2, labelItem->pos() );

  path.lineTo( labelItem->pos() );
  QPointF d1 = -parallel_unitVector * v + orthogonal_diffVector + mapFromItem( myEndItem, 0, 0 );
  QPointF d2 = /*offset +*/ mapFromItem( myEndItem, 0, 0 );
  path.cubicTo( d1, d2, mapFromItem( myEndItem, 0, 0 ) );
  return path;
}

void SceneItem_Connection::paint( QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/ ) {
//   qDebug() << __FUNCTION__ << (unsigned int)this;
  if (scene() == NULL) {
    qDebug() << "Can't paint item, not in any scene() anymore";
    return;
  }

  if ( myStartItem == NULL || myEndItem == NULL ) {
    qDebug() << "Can't draw anything since myStartItem||myEndItem isn't set yet";
    return;
  }

  if ( myStartItem->collidesWithItem( myEndItem ) ) {
    qDebug() << "Drawing a loop item";
    // draw the loop item
    if ((( GraphicsScene* )scene() )->want_boundingBox() ) {
    }
    if ((( GraphicsScene* )scene() )->want_drawItemShape() ) {
      painter->drawPath( shape() );
    }
    if ( m_highlight ) {

    } else {

    }
    if ( isSelected() ) {
    }
    return;
  }

  QPen p = pen;
  pen.setColor( m_color );
  if ( isSelected() )
    painter->setPen( pen );

  painter->drawPath( connectionPath() );

  if ((( GraphicsScene* )scene() )->want_boundingBox() ) {
    QPen p = pen;
    pen.setColor( m_color );
    painter->setPen( pen );
    QRectF bbox = boundingRect();
    painter->drawRect( bbox.adjusted( MAX_BRUSH_SIZE, MAX_BRUSH_SIZE, -MAX_BRUSH_SIZE, -MAX_BRUSH_SIZE ) );
  }
  if ((( GraphicsScene* )scene() )->want_drawItemShape() ) {
    painter->drawPath( shape() );
  }

  if ( m_highlight ) {
    QColor c = QColor( "blue" );

    c.setAlphaF( 0.2 );
    painter->setPen( QPen( c, 6, Qt::SolidLine ) );
    painter->drawPath( shape() );
  } else {
    if ((( GraphicsScene* )scene() )->want_coloredConnectionHelper() ) {
      QColor c = m_color;
      c.setAlphaF( 0.2 );
      painter->setPen( QPen( c, 12, Qt::SolidLine ) );
      painter->drawPath( shape() );
    }
  }

  if ( isSelected() ) {
    painter->setPen( QPen( QColor( "red" ), 4, Qt::DashLine ) );
    QLineF myLine = line;
    painter->drawPath( connectionPath() );
  }
//
//   QPen myPen = pen;
//   myPen.setColor( myColor );
//   qreal arrowSize = 10;
//   painter->setPen( myPen );
//   painter->setBrush( myColor );
//
//   int arrowMode = 2;
//   if ( arrowMode & 1 ) {
//     /*
//     ** draw the arrow head at the node
//     */
//     myPen.setColor( myColor );
//     painter->setPen( myPen );
//
//     double angle = ::acos( line.dx() / line.length() );
//     if ( line.dy() >= 0 )
//       angle = ( Pi * 2 ) - angle;
//
//     QPointF arrowP1 = line.p2() - QPointF( sin( angle + Pi / 3 ) * arrowSize,
//                                            cos( angle + Pi / 3 ) * arrowSize );
//     QPointF arrowP2 = line.p2() - QPointF( sin( angle + Pi - Pi / 3 ) * arrowSize,
//                                            cos( angle + Pi - Pi / 3 ) * arrowSize );
//
//     arrowHead.clear();
//     arrowHead << line.p2() << arrowP1 << arrowP2;
//
//     painter->drawPolygon( arrowHead );
//   }
//   if ( arrowMode & 2 ) {
//     /*
//     ** draw the arrow head at the label
//     */
//     myPen.setColor( myColor );
//     painter->setPen( myPen );
//
//     double angle = ::acos( line.dx() / line.length() );
//     if ( line.dy() >= 0 )
//       angle = ( Pi * 2 ) - angle;
//     QPointF drawPoint = line.pointAt( 0.5 );
//
//     QLineF uline = line.unitVector();
//     uline.setLength( CIRCLE_FOR_SYNBOL_RADIUS + 12 );
//     QPointF nv = uline.p1() - uline.p2();
//     drawPoint -= nv;
//
//     QPointF arrowP1 = drawPoint - QPointF( sin( angle + Pi / 3 ) * arrowSize,
//                                            cos( angle + Pi / 3 ) * arrowSize );
//     QPointF arrowP2 = drawPoint - QPointF( sin( angle + Pi - Pi / 3 ) * arrowSize,
//                                            cos( angle + Pi - Pi / 3 ) * arrowSize );
//
//     arrowHead.clear();
//     arrowHead << drawPoint << arrowP1 << arrowP2;
//
//     painter->drawPolygon( arrowHead );
//
//   }
}

int SceneItem_Connection::type() const {
//   qDebug() << __FUNCTION__ << (unsigned int)this;
  return SceneItem_ConnectionType;
}

void SceneItem_Connection::highlight( bool status ) {
  if ( status == true )
    m_highlight = true;
  else
    m_highlight = false;
}

void SceneItem_Connection::hoverEnterEvent( QGraphicsSceneHoverEvent * /*event*/ ) {
//   qDebug() << "hoverEnterEvent";
  if ( !(( GraphicsScene* )scene() )->want_highlight() )
    return;

  highlight( true );
  updatePosition();
}

void SceneItem_Connection::hoverLeaveEvent( QGraphicsSceneHoverEvent * /*event*/ ) {
//   qDebug() << "hoverLeaveEvent";
  highlight( false );
  updatePosition();
}

/*
** if m_customTransformation is true
**    the autolayout functionality is disabled when adding another connection or deleting an existing one.
** default is false since connections should be affected by autolayout functionality
*/
void SceneItem_Connection::setCustomTransformation( bool value ) {
  m_customTransformation = value;
  if ( !value ) {
    ooffset = 0.0;
    poffset = 0.0;
    updateLabelPosition();
    if (myStartItem != NULL)
      ((SceneItem_Node *)myStartItem)->layoutChange();
  }
}

bool SceneItem_Connection::customTransformation() {
  return m_customTransformation;
}

bool SceneItem_Connection::isLoop() {
  if ( myStartItem != NULL && myEndItem != NULL )
    return ( myStartItem == myEndItem );
  else {
    qDebug() << "critical error: this case is not handled yet " << __FUNCTION__;
    return true;
  }
}

void SceneItem_Connection::setAutoLayoutFactor(qreal factor) {
  ooffset = factor * (2*CIRCLE_FOR_SYNBOL_RADIUS /*+ 2*/);
  updateLabelPosition();
}




