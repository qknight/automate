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

#include "SceneItem_Connection.h"

const qreal Pi = 3.14;

SceneItem_Connection::SceneItem_Connection( QPersistentModelIndex index ) : QGraphicsItem() {
//   qDebug() << __FUNCTION__ << (unsigned int)this;
  m_customTransformation = false;
  labelItem = new SceneItem_ConnectionHandle;
  labelItem->setParentItem( this );
  labelItem->hide();
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

  loopPosition = QPointF( 0, 65 );
  ooffset = 0.0;
  poffset = 0.0;// this parameter means: -1 source node, 0.5 between mid and destnode, 1 destnode
}

// - connection is removed -> remove the reference from the two associated nodes
SceneItem_Connection::~SceneItem_Connection() {
//   qDebug() << __FUNCTION__ << "BEGIN" << (unsigned int)this;

  if ( myEndItem != NULL )
    if ( !myEndItem->removeConnection( this ) )
      qDebug() << "Connection wasn't removed propperly @ myEndItem";
  if ( myStartItem != NULL && myStartItem != myEndItem )
    if ( !myStartItem->removeConnection( this ) )
      qDebug() << "Connection wasn't removed propperly @ myStartItem";

  if ( myStartItem != NULL )
    (( SceneItem_Node * )myStartItem )->layoutChange();
  if ( myEndItem != NULL )
    (( SceneItem_Node * )myEndItem )->layoutChange();

  labelItem->deleteLater();
}

void SceneItem_Connection::updateData() {
//   qDebug() << __FUNCTION__ << (unsigned int)this;
  if ( scene() == NULL ) {
    qDebug() << "item isn't in any scene, can't query for valid data";
    return;
  }
  bool forceLayoutUpdate = false;

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

  // new connections which point to nowhere are filtered here
  if ( !next_node_index.isValid() ) {
    return;
  }

  // is this item initalized yet? or is this a 'new connection'?
  QGraphicsItem* b = (( GraphicsScene* )scene() )->modelToSceenIndex( next_node_index );
  if ( b == NULL ) {
    // we do not want to show broken connections -> as none initalized are...
    labelItem->hide();
    return;
  }

  // - a new connection is made (usual case)
  SceneItem_Node *s = ( SceneItem_Node * )a;
  SceneItem_Node *e = ( SceneItem_Node * )b;
  s->addConnection( this );

  // destination changed: layoutChange in partent node forced
  if ( myEndItem != e )
    forceLayoutUpdate = true;

  myStartItem = s;

  if ( myEndItem != NULL && myEndItem != e && myStartItem != myEndItem ) {
//     qDebug() << " ----> e" << (unsigned int)e;
//     qDebug() << " ----> myEndItem" << (unsigned int)myEndItem;
    if ( myEndItem != NULL )
      myEndItem->removeConnection( this );
    e->addConnection( this );
  }

  myEndItem = e;

  if ( s != e ) {
//     qDebug() << "adding connection to new endItem";
    myEndItem->addConnection( this );
  }

//   qDebug() << "id of changed item " << ((GraphicsScene*)scene())->data( index, customRole::IdRole ).toInt();
  if ( myStartItem == myEndItem ) {
    // loop item handling
    setLoopPosition( loopPosition );
    line = createLine( mapFromItem( myStartItem, 0, 0 ), labelItem->pos() );
  } else {
    // normal connection handling
    line = createLine( mapFromItem( myStartItem, 0, 0 ), mapFromItem( myEndItem, 0, 0 ) );
  }
  updateLabelPosition();

  // create a new layout since connections have changed
  if ( forceLayoutUpdate )
    s->layoutChange();

//   qDebug() << "myStartItem" << (unsigned int)myStartItem;
//   qDebug() << "myEndItem" << (unsigned int)myEndItem;

  // we want to draw connection handles of loops and valid connections
  // but we don't want to see the connection label or a uninitalized connection.
  // two cases:
  // - valid connection here
  // - loop connection
  labelItem->show();

  // redraw the Connection
  update();
}

void SceneItem_Connection::updatePosition() {
//   qDebug() << __FUNCTION__ << (unsigned int)this;
  prepareGeometryChange();
  if ( isLoop() ) {
    // loop case
    labelItem->setPos( mapFromItem( myStartItem, 0, 0 ) + loopPosition + QPointF( 0, ooffset ) );
  } else {
    // normal connection case
    line = createLine( mapFromItem( myStartItem, 0, 0 ), mapFromItem( myEndItem, 0, 0 ) );
    updateLabelPosition();
  }
  update();
}

void SceneItem_Connection::labelItemPositionChangeCallback( const QPointF& /*oldPos*/, const QPointF& newPos ) {
//   qDebug() << __FUNCTION__ << (unsigned int)this;
  prepareGeometryChange();
  if ( isLoop() ) {
    loopPosition = newPos - myStartItem->pos();
  } else {
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

  }
  // finally update what we want to see
  update();
}

void SceneItem_Connection::updateLabelPosition() {
//   qDebug() << __FUNCTION__ << (unsigned int)this;
  if ( isLoop() ) {
    labelItem->setPos( mapFromItem( myStartItem, 0, 0 ) + loopPosition + QPointF( 0, ooffset ) );
    return;
  }

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

QLineF SceneItem_Connection::createLine( QPointF a, QPointF b ) {
//   qDebug() << __FUNCTION__ << (unsigned int)this;
  if ( myStartItem->collidesWithItem( myEndItem ) ) {
    // loop item line handling
    return QLineF( a, b );
  }

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
  if ( myStartItem == NULL || myEndItem == NULL )
    return QPainterPath();

  if ( myStartItem->collidesWithItem( myEndItem ) ) {
    // loop item handling
    QPointF virtualmidpoint = myStartItem->pos() / 2.0 + labelItem->pos() / 2.0;
    QPainterPath z( myStartItem->pos() );
#define RR 30
    z.cubicTo( virtualmidpoint + QPointF( RR, 0 ), labelItem->pos() + QPointF( RR / 2, 0 ), labelItem->pos() );
    z.cubicTo( labelItem->pos() - QPointF( RR / 2, 0 ), virtualmidpoint - QPointF( RR, 0 ), myStartItem->pos() );
    return z;
  }
  // this fixed another issue...
  if ( line.length() == 0 )
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

//   path.cubicTo( a1, a2, labelItem->pos() );
  path.lineTo( labelItem->pos() );

  QPointF d1 = -parallel_unitVector * v + orthogonal_diffVector + mapFromItem( myEndItem, 0, 0 );
  QPointF d2 = /*offset +*/ mapFromItem( myEndItem, 0, 0 );

//   path.cubicTo( d1, d2, mapFromItem( myEndItem, 0, 0 ) );
  path.lineTo( mapFromItem( myEndItem, 0, 0 ) );

  return path;
}

/*! draw the connection which can either be a loop or a normal connection
** this algorithm does only do the drawing and can't differentiate if it
** must draw a loop or a normal connection.
*/
void SceneItem_Connection::paint( QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/ ) {
//   qDebug() << __FUNCTION__ << (unsigned int)this;
  if ( scene() == NULL ) {
    qDebug() << "Can't paint: this connection is not in any scene() anymore";
    return;
  }

  if ( myStartItem == NULL || myEndItem == NULL ) {
    qDebug() << "Can't draw anything since myStartItem||myEndItem isn't set yet";
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

  QPen myPen = pen;
  myPen.setColor( myColor );
  qreal arrowSize = 10;
  painter->setPen( myPen );
  painter->setBrush( myColor );

  if ( isLoop() )
    return;

  /*
  ** draw the arrow head at the node
  ** -> we can only draw arrows if the line length is not shorter than we can handle
  */
  QLineF line = createLine( labelItem->pos(), mapFromItem( myEndItem, 0, 0 ) );
  if ( line.length() > 0.0 ) {
    myPen.setColor( myColor );
    painter->setPen( myPen );

    double angle = ::acos( line.dx() / line.length() );
    if ( line.dy() >= 0 )
      angle = ( Pi * 2 ) - angle;

    QPointF arrowP1 = line.p2() - QPointF( sin( angle + Pi / 3 ) * arrowSize,
                                           cos( angle + Pi / 3 ) * arrowSize );
    QPointF arrowP2 = line.p2() - QPointF( sin( angle + Pi - Pi / 3 ) * arrowSize,
                                           cos( angle + Pi - Pi / 3 ) * arrowSize );

    arrowHead.clear();
    arrowHead << line.p2() << arrowP1 << arrowP2;

    painter->drawPolygon( arrowHead );
  }
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

/*!
** if m_customTransformation is true
**    the autolayout functionality is disabled when adding another connection or deleting an existing one.
** default is false since connections should be affected by autolayout functionality
*/
void SceneItem_Connection::setCustomTransformation( bool value ) {
  if (isLoop())
    return;
  m_customTransformation = value;
  if ( !value ) {
    prepareGeometryChange();
    ooffset = 0.0;
    poffset = 0.0;
    updateLabelPosition();
    if ( myStartItem != NULL )
      (( SceneItem_Node * )myStartItem )->layoutChange();
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

void SceneItem_Connection::setAutoLayoutFactor( qreal factor ) {
  ooffset = factor * ( 2 * CIRCLE_FOR_SYNBOL_RADIUS /*+ 2*/ );
  updateLabelPosition();
}

void SceneItem_Connection::setLoopPosition( QPointF newPos ) {
  //FIXME prepareGeometryChange and misc
  prepareGeometryChange();
  loopPosition = newPos;
  updatePosition();
  update();
}


