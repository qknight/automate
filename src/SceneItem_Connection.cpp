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

#include <QtGui>

#include "SceneItem_Connection.h"
#include <math.h>

const qreal Pi = 3.14;
#define CIRCLE_FOR_SYNBOL_RADIUS 14

SceneItem_Connection::SceneItem_Connection( QPersistentModelIndex index ) : QGraphicsItem() {
//   qDebug() << "Creating a new connection";
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
}

SceneItem_Connection::~SceneItem_Connection() { }

void SceneItem_Connection::updateData() {
  if ( scene() == NULL ) {
    qDebug() << "item isn't in any scene, can't query for valid data";
    return;
  }

  unsigned int id = (( GraphicsScene* )scene() )->data( index, customRole::IdRole ).toInt();
  QString toolTip = QString( "c%1" ).arg( id );
  setToolTip( toolTip );

  prepareGeometryChange();
  unsigned int symbol_index = (( GraphicsScene* )scene() )->data( index, customRole::SymbolIndexRole ).toInt();
  this->symbol_index = symbol_index;

  QGraphicsItem* a = (( GraphicsScene* )scene() )->modelToSceenIndex( QPersistentModelIndex( index.parent() ) );
  if ( a == NULL )
    return;
  QModelIndex next_node_index = (( Model* )index.model() )->next_nodeModelIndex( index );
  if ( !next_node_index.isValid() ) {
    qDebug() << "Critical error because next_node isn't a valid index";
    qDebug() << __FILE__ << __FUNCTION__ << __LINE__;
    exit( 0 );
  }
  QGraphicsItem* b = (( GraphicsScene* )scene() )->modelToSceenIndex( next_node_index );
  if ( b == NULL )
    return;
  symbol_index = (( GraphicsScene* )scene() )->data( index, customRole::SymbolIndexRole ).toInt();

  (( SceneItem_Node * )a )->addConnection( this );
  (( SceneItem_Node * )b )->addConnection( this );
  SceneItem_Node *s = (( SceneItem_Node * )a );
  SceneItem_Node *e = (( SceneItem_Node * )b );

  myStartItem = s;
  myEndItem = e;

//   qDebug() << "id of changed item " << ((GraphicsScene*)scene())->data( index, customRole::IdRole ).toInt();
  line = createLine( mapFromItem( myStartItem, 0, 0 ), mapFromItem( myEndItem, 0, 0 ) );

  update();
}

QLineF SceneItem_Connection::createLine( QPointF a, QPointF b ) {
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
  qreal extra = ( pen.width() + 20 ) / 2.0;
  QRectF bbox = QRectF( line.p1(), QSizeF( line.p2().x() - line.p1().x(),
                        line.p2().y() - line.p1().y() ) )
                .normalized()
                .adjusted( -extra, -extra, extra, extra );
  int z = CIRCLE_FOR_SYNBOL_RADIUS / 2;

  if ( bbox.width() < 2*CIRCLE_FOR_SYNBOL_RADIUS ) {
    bbox = bbox.adjusted( -z, 0, z, 0 );
  }
  if ( bbox.height() < 2*CIRCLE_FOR_SYNBOL_RADIUS ) {
    bbox = bbox.adjusted( 0, -z, 0, z );
  }
  return bbox;
}

QPainterPath SceneItem_Connection::shape() const {
#define CLICKABLERANGE 6
  QPointF down1, down2, up1, up2, nv;
  QPolygonF p;
  // 1. create the normal vector NV on point line.p1()
  // 2. and resize it to be CLICKABLERANGE pixels long
  QLineF a = line.normalVector().unitVector();
  a.setLength( CLICKABLERANGE );
  nv = a.p1() - a.p2();
  down1 = line.p1() + nv;
  down2 = line.p1() - nv;
  up1 = line.p2() - nv;
  up2 = line.p2() + nv;

  p << down1 << down2 << up1 << up2 << down1;
  QPainterPath path;
  path.addPolygon( p );
  path.addPolygon( arrowHead );
  // maybe add labelbox as well?
  return path;
}

void SceneItem_Connection::updatePosition() {
  prepareGeometryChange();
  line = createLine( mapFromItem( myStartItem, 0, 0 ), mapFromItem( myEndItem, 0, 0 ) );
  update();
}

void SceneItem_Connection::paint( QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/ ) {
  if ( myStartItem ==  myEndItem ) {
    return;
  }

  if ( myStartItem == NULL || myEndItem == NULL ) {
    qDebug() << "Can't draw anything since myStartItem||myEndItem isn't set yet";
    return;
  }
  painter->drawLine( line );
// this is a nice feature for debugging
  QPen p = pen;
  pen.setColor( m_color );
  painter->setPen( pen );

  if ((( GraphicsScene* )scene() )->want_boundingBox() ) {
    painter->drawRect( boundingRect() );
  }
  if ((( GraphicsScene* )scene() )->want_drawItemShape() ) {
    painter->drawPath( shape() );
  }

  pen = p;

  if ( myStartItem->collidesWithItem( myEndItem ) )
    return;

  if ( m_highlight ) {
    QColor c = QColor( "blue" );
    c.setAlphaF( 0.05 );
    painter->setPen( QPen( c, 22, Qt::SolidLine ) );
    painter->drawLine( line );
    c.setAlphaF( 0.1 );
    painter->setPen( QPen( c, 8, Qt::SolidLine ) );
    painter->drawLine( line );
  } else
    if ((( GraphicsScene* )scene() )->want_coloredConnectionHelper() ) {
      QColor c = m_color;
      c.setAlphaF( 0.2 );
      painter->setPen( QPen( c, 12, Qt::SolidLine ) );
      painter->drawLine( line );
    }

  if ( isSelected() ) {
    painter->setPen( QPen( QColor( "red" ), 4, Qt::DashLine ) );
    QLineF myLine = line;
    painter->drawLine( myLine );
  }

  QPen myPen = pen;
  myPen.setColor( myColor );
  qreal arrowSize = 10;
  painter->setPen( myPen );
  painter->setBrush( myColor );

  // additional label code
  QPointF vpos = myStartItem->pos() / 2 + myEndItem->pos() / 2;

  QColor c = QColor( "lightgrey" );
  c.setAlphaF( 0.9 );
  myPen.setColor( c );
  painter->setPen( myPen );
  painter->setBrush( c );
  QRectF rectangle( vpos.x() - CIRCLE_FOR_SYNBOL_RADIUS, vpos.y() -
                    CIRCLE_FOR_SYNBOL_RADIUS, 2*CIRCLE_FOR_SYNBOL_RADIUS, 2*CIRCLE_FOR_SYNBOL_RADIUS );
  painter->drawEllipse( rectangle );

  myPen.setColor( myColor );
  painter->setPen( myPen );
  painter->setBrush( myColor );

  QString label;
  if ((( GraphicsScene* )scene() )->want_customConnectionLabels() ) {
    label = (( GraphicsScene * )scene() )->data( index, customRole::CustomLabelRole ).toString();
    if (label.size() == 0)
      label = QString( "%1" ).arg( symbol_index );
  } else {
    label = QString( "%1" ).arg( symbol_index );
  }
  QFont f;
  QFontMetrics fm( f );
  int width = fm.width( label );
  int height = fm.height();
  painter->drawText( QPointF( -width / 2, height / 4 ) + vpos, label );

  int arrowMode = 2;
  if ( arrowMode & 1 ) {
    /*
    ** draw the arrow head at the node
    */
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
  if ( arrowMode & 2 ) {
    /*
    ** draw the arrow head at the label
    */
    myPen.setColor( myColor );
    painter->setPen( myPen );

    double angle = ::acos( line.dx() / line.length() );
    if ( line.dy() >= 0 )
      angle = ( Pi * 2 ) - angle;
    QPointF drawPoint = line.pointAt( 0.5 );

    QLineF uline = line.unitVector();
    uline.setLength( CIRCLE_FOR_SYNBOL_RADIUS + 12 );
    QPointF nv = uline.p1() - uline.p2();
    drawPoint -= nv;

    QPointF arrowP1 = drawPoint - QPointF( sin( angle + Pi / 3 ) * arrowSize,
                                           cos( angle + Pi / 3 ) * arrowSize );
    QPointF arrowP2 = drawPoint - QPointF( sin( angle + Pi - Pi / 3 ) * arrowSize,
                                           cos( angle + Pi - Pi / 3 ) * arrowSize );

    arrowHead.clear();
    arrowHead << drawPoint << arrowP1 << arrowP2;

    painter->drawPolygon( arrowHead );

  }
}

int SceneItem_Connection::type() const {
  return SceneItem_ConnectionType;
}

void SceneItem_Connection::highlight( bool status ) {
  if ( status == true )
    m_highlight = true;
  else
    m_highlight = false;
}

void SceneItem_Connection::setSymbol_Index( unsigned int symbol_index ) {
  if ( this->symbol_index == symbol_index )
    return;
  this->symbol_index = symbol_index;
  update();
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


void SceneItem_Connection::mouseDoubleClickEvent( QGraphicsSceneMouseEvent * /*event*/ ) {
  qDebug() << __FUNCTION__;
}
