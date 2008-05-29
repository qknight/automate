//
// C++ Implementation: SceneItem_FlexibleConnection
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "SceneItem_FlexibleConnection.h"

SceneItem_FlexibleConnection::SceneItem_FlexibleConnection( QGraphicsScene* scene ) : QGraphicsItem() {
  m_scene=scene;
  QGraphicsItem* s1 = (QGraphicsItem*)addHandle(handleType::start,this);
  addHandle(handleType::start_handle,s1);
  QGraphicsItem* m1 = addHandle(handleType::intermediate,this);
  QGraphicsItem* e1 = (QGraphicsItem*)addHandle(handleType::end,this);
  addHandle(handleType::end_handle, e1);
  s1->setPos(-200,0);
  m1->setPos(0,0);
  e1->setPos(200,0);

  start = QPointF( -200, 0 );
  intermediate = QPointF( 0, 0 );
  end = QPointF( 200, 0 );
  start_handle = QPointF( 0, 0 ) + start;
  end_handle = QPointF( 0, 0 ) + end;
}

SceneItem_FlexibleConnection::~SceneItem_FlexibleConnection() { }

QGraphicsItem* SceneItem_FlexibleConnection::addHandle(handleType::itemType type, QGraphicsItem* h) {
  ScneItem_FlexibleHandle* h1 = new ScneItem_FlexibleHandle(type);
  m_scene->addItem( h1 );
  h1->setParentItem( h );
  return (QGraphicsItem*) h1;
}

void SceneItem_FlexibleConnection::paint( QPainter *painter,
                                          const QStyleOptionGraphicsItem */*option*/,
                                          QWidget */*widget*/ ) {
  painter->drawRect(boundingRect());
  QPainterPath qp( start );

  QLineF l1( start, start_handle );
  QPointF fixed_start_handle = l1.pointAt( 0.3 );
  qp.cubicTo( start_handle, fixed_start_handle, intermediate );

  QLineF l2( end, end_handle );
  QPointF fixed_end_handle = l2.pointAt( 0.3 );
  qp.cubicTo( fixed_end_handle, end_handle, end );

  painter->drawPath( qp );

  painter->setPen( QPen( QColor( "red" ) ) );

  painter->drawLine(QLineF(start,start_handle));
  painter->drawLine(QLineF(end,end_handle));
}

QRectF SceneItem_FlexibleConnection::boundingRect() const {
  return QRectF( -300, -300, 600, 600);
}

void SceneItem_FlexibleConnection::handleChanged(QPointF newpos, int t) {
  switch(t) {
    case handleType::start:
      start=newpos;
      forcedHandlePosUpdate(QLineF(start,end).pointAt(0.5),handleType::intermediate);
      break;
    case handleType::start_handle:
      start_handle=newpos;
      break;
    case handleType::intermediate:
      intermediate=newpos;
      break;
    case handleType::end_handle:
      end_handle=newpos;
      break;
    case handleType::end:
      end=newpos;
      forcedHandlePosUpdate(QLineF(start,end).pointAt(0.5),handleType::intermediate);
      break;
  }
  update();
}

void SceneItem_FlexibleConnection::forcedHandlePosUpdate(QPointF p, int type) {
  foreach(QGraphicsItem* child, children() )
    if (child->type() == type)
      child->setPos(p);
}
