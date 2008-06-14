//
// C++ Implementation: SceneItem_ConnectionLabel
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "SceneItem_ConnectionLabel.h"
// http://lists.trolltech.com/qt-interest/2007-03/thread00929-0.html
SceneItem_ConnectionLabel::SceneItem_ConnectionLabel() : QGraphicsTextItem() {
  setFlag( QGraphicsItem::ItemIsFocusable );
  setFlag( QGraphicsItem::ItemIsMovable );
//   setFlag(QGraphicsItem::ItemIsSelectable);
//   setZValue( 100 );
  d = new QTextDocument;
  setTextInteractionFlags( Qt::TextEditable );
  d->setHtml( "unset" );
  setDocument( d );
  move_object_on_mouseMove = false;
}

void SceneItem_ConnectionLabel::setLabel( QString label ) {
  setTextInteractionFlags( Qt::TextEditable );
  d->setHtml( label );
  setDocument( d );
  m_label = label;
}

SceneItem_ConnectionLabel::~SceneItem_ConnectionLabel() {

}

QPainterPath SceneItem_ConnectionLabel::shape() const {
  QRectF r( -CIRCLE_FOR_SYNBOL_RADIUS, -CIRCLE_FOR_SYNBOL_RADIUS, 2*CIRCLE_FOR_SYNBOL_RADIUS, 2*CIRCLE_FOR_SYNBOL_RADIUS );
  r.adjusted( -3, -3, 3, 3 );
  QPainterPath path;
  path.addPolygon( r );

  return path;
}


QRectF SceneItem_ConnectionLabel::boundingRect() const {
  QRectF r( -CIRCLE_FOR_SYNBOL_RADIUS, -CIRCLE_FOR_SYNBOL_RADIUS, 2*CIRCLE_FOR_SYNBOL_RADIUS, 2*CIRCLE_FOR_SYNBOL_RADIUS );
  r.adjusted( -3, -3, 3, 3 );
  return r;
}

void SceneItem_ConnectionLabel::paint( QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/ ) {
//   painter->drawRect( boundingRect() );
  QColor c;
  if ( isSelected() )
    c = QColor( "red" );
  else
    c = QColor( "lightgrey" );
  QPen myPen;
  c.setAlphaF( 0.9 );
  myPen.setColor( c );
  painter->setPen( myPen );
  painter->setBrush( c );
  QRectF rectangle( -CIRCLE_FOR_SYNBOL_RADIUS, -CIRCLE_FOR_SYNBOL_RADIUS,
                    2*CIRCLE_FOR_SYNBOL_RADIUS, 2*CIRCLE_FOR_SYNBOL_RADIUS );
//   rectangle.moveTopLeft(diff);
  painter->drawEllipse( rectangle );

  myPen.setColor( QColor( "black" ) );
  painter->setPen( myPen );
//   painter->setBrush( myColor );

//   QString label="34";
  /*  if ((( GraphicsScene* )scene() )->want_customConnectionLabels() ) {
      label = (( GraphicsScene * )scene() )->data( index, customRole::CustomLabelRole ).toString();
      if ( label.size() == 0 )
        label = QString( "%1" ).arg( symbol_index );
    } else {
      label = QString( "%1" ).arg( symbol_index );
    }*/
  QFont f;
  QFontMetrics fm( f );
  int width = fm.width( m_label );
  int height = fm.height();
  painter->drawText( QPointF( -width / 2, height / 4 ), m_label );
}

// void SceneItem_ConnectionLabel::focusInEvent( QFocusEvent *event ) {
// //   QGraphicsTextItem::focusInEvent(event);
// //   qDebug() << __FUNCTION__ << toPlainText();
// }
//
// void SceneItem_ConnectionLabel::focusOutEvent( QFocusEvent *event ) {
//   if ( m_label != toPlainText() )
//     qDebug() << __FUNCTION__ << "label changed to " << toPlainText();
//   m_label = toPlainText();
//   //FIXME request a label change in the model
//   setTextInteractionFlags( Qt::NoTextInteraction );
//   QGraphicsTextItem::focusOutEvent( event );
//   update();
// }

void SceneItem_ConnectionLabel::mousePressEvent( QGraphicsSceneMouseEvent * event ) {
  move_object_on_mouseMove = true;
//   QGraphicsTextItem::mousePressEvent(event);
}

void SceneItem_ConnectionLabel::mouseMoveEvent( QGraphicsSceneMouseEvent * event ) {
  if ( move_object_on_mouseMove ) {
    moveBy( event->lastPos().x(), event->lastPos().y() );
//     if (parentItem() != NULL)
//       parentItem()->update();
  }
}

void SceneItem_ConnectionLabel::mouseReleaseEvent( QGraphicsSceneMouseEvent * event ) {
  move_object_on_mouseMove = false;
}

void SceneItem_ConnectionLabel::mouseDoubleClickEvent( QGraphicsSceneMouseEvent * event ) {
  setTextInteractionFlags( Qt::TextEditable );
  //FIXME add select all text
}

QVariant SceneItem_ConnectionLabel::itemChange( GraphicsItemChange change, const QVariant & value ) {
  // only send this event when the labelItem is moved manually
  if ( move_object_on_mouseMove ) {
    if ( change == ItemPositionChange && scene() ) {
      // pos() is the old position, value is the new position.
      if ( parentItem() != NULL )
        (( SceneItem_Connection* )parentItem() )->labelItemPositionUpdate( pos(), value.toPointF() );
    }
  }
  return QGraphicsTextItem::itemChange( change, value );
}

