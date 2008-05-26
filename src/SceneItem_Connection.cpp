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

SceneItem_Connection::SceneItem_Connection( QPersistentModelIndex index, int value, SceneItem_Node *startItem, SceneItem_Node *endItem ) : QGraphicsItem() {
//   qDebug() << "Creating a new connection";
  this->value = value;
  this->index = index;
  m_highlight = false;

  // needed for debugging, remove later
  m_color = QColor(qrand()%255,qrand()%255,qrand()%255,255);

  myStartItem = startItem;
  myEndItem = endItem;
  setFlag( QGraphicsItem::ItemIsSelectable, true );
  myColor = Qt::black;
  pen = QPen( myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );
  line = createLine( mapFromItem( myStartItem, 0, 0 ), mapFromItem( myEndItem, 0, 0 ) );
}

SceneItem_Connection::~SceneItem_Connection() { }

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
  int z = CIRCLE_FOR_SYNBOL_RADIUS/2;

  if ( bbox.width() < 2*CIRCLE_FOR_SYNBOL_RADIUS ) {
    bbox = bbox.adjusted( -z, 0, z, 0 );
  }
  if ( bbox.height() < 2*CIRCLE_FOR_SYNBOL_RADIUS ) {
    bbox = bbox.adjusted( 0, -z, 0, z );
  }
  return bbox;
}

QPainterPath SceneItem_Connection::shape() const {
  QPainterPath path(line.p1());
  path.lineTo(line.p2());
  path.addPolygon( arrowHead );
  return path;
}

void SceneItem_Connection::updatePosition() {
  line = createLine( mapFromItem( myStartItem, 0, 0 ), mapFromItem( myEndItem, 0, 0 ) );
  update();
}

void SceneItem_Connection::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) {
  painter->drawLine( line );
// this is a nice feature for debugging
  QPen p = pen;
  pen.setColor(m_color);
  painter->setPen(pen);
  QRectF r = boundingRect();
  int extra = -4;
  r.adjusted( extra, extra, -extra, -extra );
//   painter->drawRect( r );painter->drawRect( boundingRect() );
//   return;
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
  }

  if ( isSelected() ) {
    //FIXME the line offset must be drawn by the normal of the line and not as done right now
    painter->setPen( QPen( QColor( "red" ), 1, Qt::DashLine ) );
    QLineF myLine = line;
    myLine.translate( 0, 4.0 );
    painter->drawLine( myLine );
    myLine.translate( 0, -8.0 );
    painter->drawLine( myLine );
  }

  QPen myPen = pen;
  myPen.setColor( myColor );
  qreal arrowSize = 10;
  painter->setPen( myPen );
  painter->setBrush( myColor );

  QPointF p1 = myEndItem->pos();

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

  QString label = QString( "%1" ).arg( value );
  QFont f;
  QFontMetrics fm( f );
  int width = fm.width( label );
  int height = fm.height();
  painter->drawText( QPointF( -width / 2, height / 4 ) + vpos, label );

  myPen.setColor( myColor );
  painter->setPen( myPen );

  double angle = ::acos( line.dx() / line.length() );
  if ( line.dy() >= 0 )
    angle = ( Pi * 2 ) - angle;

  QPointF arrowP1 = line.p1() + QPointF( sin( angle + Pi / 3 ) * arrowSize,
                                         cos( angle + Pi / 3 ) * arrowSize );
  QPointF arrowP2 = line.p1() + QPointF( sin( angle + Pi - Pi / 3 ) * arrowSize,
                                         cos( angle + Pi - Pi / 3 ) * arrowSize );

  arrowHead.clear();
  arrowHead << line.p1() << arrowP1 << arrowP2;

  painter->drawPolygon( arrowHead );
}


int SceneItem_Connection::type() {
  return SceneItem_ConnectionType;
}

void SceneItem_Connection::highlight( bool status ) {
  if ( status == true )
    m_highlight = true;
  else
    m_highlight = false;
}

