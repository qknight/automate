//
// C++ Implementation: ScneItem_FlexibleHandle
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "ScneItem_FlexibleHandle.h"

ScneItem_FlexibleHandle::ScneItem_FlexibleHandle( int type ) : QGraphicsItem() {
  m_type = type;
  setFlags( QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable );
}


ScneItem_FlexibleHandle::~ScneItem_FlexibleHandle() {
}

QRectF ScneItem_FlexibleHandle::boundingRect() const {
  QRectF r( -5, -5, 10, 10 );
  r.adjusted( -3, -3, 3, 3 );
  return r;
}

void ScneItem_FlexibleHandle::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) {
  if ( isSelected() )
    painter->setPen( QPen( QColor( "red" ), 3 ) );
  else
    if ( type() == handleType::start_handle || type() == handleType::end_handle ) {
      painter->setPen( QPen( QColor( "green" ), 3 ) );
    } else {
      painter->setPen( QPen( QColor( "black" ), 2 ) );
    }
  painter->drawEllipse( QRectF( QPointF( -5, -5 ), QPointF( 5, 5 ) ) );
}

QVariant ScneItem_FlexibleHandle::itemChange( GraphicsItemChange change, const QVariant & value ) {
  if ( change == ItemPositionChange && scene() ) {
    QPointF newPos = value.toPointF();
    if ( type() == handleType::start_handle || type() == handleType::end_handle ) {
      (( ScneItem_FlexibleHandle* )parentItem() )->handleChanged( mapToParent ( newPos ), type() );
    } else {
      (( SceneItem_FlexibleConnection* )parentItem() )->handleChanged( newPos, type() );
    }
  }

  return QGraphicsItem::itemChange( change, value );
}

int ScneItem_FlexibleHandle::type() const {
  return m_type;
}

void ScneItem_FlexibleHandle::handleChanged( QPointF newpos, int t ) {
//   if ( parentItem() != NULL )
  (( SceneItem_FlexibleConnection* )parentItem() )->handleChanged( newpos, t );
}
