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


#include "SceneItem_ConnectionHandle.h"
// http://lists.trolltech.com/qt-interest/2007-03/thread00929-0.html

SceneItem_ConnectionHandle::SceneItem_ConnectionHandle() : QGraphicsItem() {
//   qDebug() << __FUNCTION__;
  setFlag( QGraphicsItem::ItemIsMovable );
  move_object_on_mouseMove = false;
  move_object_on_mouseMove_used = false;
}

void SceneItem_ConnectionHandle::setLabel( QString label ) {
  m_label = label;
  update();
}

SceneItem_ConnectionHandle::~SceneItem_ConnectionHandle() {
//   qDebug() << __FUNCTION__;
}

QPainterPath SceneItem_ConnectionHandle::shape() const {
  QRectF r( -CIRCLE_FOR_SYNBOL_RADIUS, -CIRCLE_FOR_SYNBOL_RADIUS, 2*CIRCLE_FOR_SYNBOL_RADIUS, 2*CIRCLE_FOR_SYNBOL_RADIUS );
  r.adjusted( -3, -3, 3, 3 );
  QPainterPath path;
  path.addEllipse( r );

  return path;
}


QRectF SceneItem_ConnectionHandle::boundingRect() const {
  //FIXME on very long labels we could adjust the boundingRect() with the rendered text width/height
  //      right now text is croped until the scene is completely redrawn most of the time the label
  //      will be cut and this looks bugggy
  QRectF r( -CIRCLE_FOR_SYNBOL_RADIUS, -CIRCLE_FOR_SYNBOL_RADIUS, 2*CIRCLE_FOR_SYNBOL_RADIUS, 2*CIRCLE_FOR_SYNBOL_RADIUS );
  r.adjusted( -3, -3, 3, 3 );
  return r;
}

void SceneItem_ConnectionHandle::paint( QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/ ) {
//   painter->drawPath( shape() );
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


void SceneItem_ConnectionHandle::mousePressEvent( QGraphicsSceneMouseEvent * /*event*/ ) {
  move_object_on_mouseMove = true;
  move_object_on_mouseMove_used = false;
//   QGraphicsTextItem::mousePressEvent(event);
}

void SceneItem_ConnectionHandle::mouseMoveEvent( QGraphicsSceneMouseEvent * event ) {
  if ( move_object_on_mouseMove ) {
    move_object_on_mouseMove_used = true;
    moveBy( event->lastPos().x(), event->lastPos().y() );
//     if (parentItem() != NULL)
//       parentItem()->update();
  }
}

void SceneItem_ConnectionHandle::mouseReleaseEvent( QGraphicsSceneMouseEvent * /*event*/ ) {
  move_object_on_mouseMove = false;
  if (!move_object_on_mouseMove_used) {
    if (((SceneItem_Connection*)parentItem())->isLoop())
      parentItem()->setSelected(!parentItem()->isSelected());
  }
}

void SceneItem_ConnectionHandle::mouseDoubleClickEvent( QGraphicsSceneMouseEvent * event ) {
  addEditor(event);
}

void SceneItem_ConnectionHandle::addEditor(QGraphicsSceneMouseEvent * event) {
  SceneItem_LabelEditor* f = new SceneItem_LabelEditor( this );
  f->setZValue( 1000.0 );
  f->setTextInteractionFlags( Qt::TextEditorInteraction );
  f->setPos(event->pos());
  f->setTextInteractionFlags(Qt::TextEditorInteraction);
//   f->setPlainText(m_label);
  f->setFocus();
}

QVariant SceneItem_ConnectionHandle::itemChange( GraphicsItemChange change, const QVariant & value ) {
  // only end this event when the labelItem is moved manually
  if ( move_object_on_mouseMove ) {
    if ( parentItem() != NULL )
      (( SceneItem_Connection* )parentItem() )->setCustomTransformation( true );
    if ( scene() && change == ItemPositionChange ) {
      // pos() is the old position, value is the new position.
      if ( parentItem() != NULL ) {
        (( SceneItem_Connection* )parentItem() )->labelItemPositionChangeCallback( pos(), value.toPointF() );
      }
    }
  }
  return QGraphicsItem::itemChange( change, value );
}

void SceneItem_ConnectionHandle::contextMenuEvent( QGraphicsSceneContextMenuEvent * event ) {

  // to reduce the overhead of QObject used in EVERY (this)-class one can move that code
  // into the scene and popup the context menu from there which is much more efficient
  // remember to check for item existence before applying any function on (this) since
  // the item can be removed while the context menu is still valid then....
  QMenu menu;
//   QAction *removeConnectionAction = menu.addAction( "Remove connection" );
//   QAction *editLabelAction = menu.addAction( "Edit Label" );
  QAction *removeTransformationAction = menu.addAction( "Remove custom transformation" );

  //   connect(removeConnectionAction,SIGNAL(triggered()),this,SLOT(removeConnectionSlot()));
//   connect(editLabelAction,SIGNAL(triggered()),this,SLOT(editLabelSlot()));
  connect(removeTransformationAction,SIGNAL(triggered()),this,SLOT(removeTransformationSlot()));
  menu.exec( event->screenPos() );
}

int SceneItem_ConnectionHandle::type() const {
  return SceneItem_ConnectionHandleType;
}

/*void SceneItem_ConnectionHandle::removeConnectionSlot() {
  qDebug() << __FUNCTION__;
}*/

void SceneItem_ConnectionHandle::removeTransformationSlot() {
  move_object_on_mouseMove=false;
  if ( parentItem() != NULL ) {
//     qDebug() << "disabling custom transformation";
    (( SceneItem_Connection* )parentItem() )->setCustomTransformation( false );
  }
}

void SceneItem_ConnectionHandle::editLabelSlot() {
  /*
  ** Some code is missing to make this function usable
  */
//   addEditor();
}



