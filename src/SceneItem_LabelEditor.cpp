//
// C++ Implementation: SceneItem_LabelEditor
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "SceneItem_LabelEditor.h"

// http://lists.trolltech.com/qt-interest/2007-03/thread00929-0.html
SceneItem_LabelEditor::SceneItem_LabelEditor( SceneItem_ConnectionHandle* parent ) : QGraphicsTextItem() {
  this->parent = parent;
//   d = document();//new QTextDocument;
//   d->setPlainText( "unset" );
//   setTextInteractionFlags( Qt::TextEditable );
//   d->find(QRegExp("(.*"));
//   qDebug() << __FUNCTION__;
}

SceneItem_LabelEditor::~SceneItem_LabelEditor() {
  qDebug() << __FUNCTION__;
}

void SceneItem_LabelEditor::focusInEvent( QFocusEvent *event ) {
  QGraphicsTextItem::focusInEvent( event );
}

void SceneItem_LabelEditor::focusOutEvent( QFocusEvent *event ) {
  QGraphicsTextItem::focusOutEvent( event );
  parent->requestLabelChange( document()->toPlainText() );
  delete this;
}

// QVariant SceneItem_LabelEditor::itemChange( GraphicsItemChange change, const QVariant & value ) {
//   // only send this event when the labelItem is moved manually
//   if ( move_object_on_mouseMove ) {
//     if ( change == ItemPositionChange && scene() ) {
//       // pos() is the old position, value is the new position.
//       if ( parentItem() != NULL )
//         (( SceneItem_Connection* )parentItem() )->labelItemPositionUpdate( pos(), value.toPointF() );
//     }
//   }
//   return QGraphicsItem::itemChange( change, value );
// }


