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
SceneItem_LabelEditor::SceneItem_LabelEditor( QGraphicsItem* parent ) : QGraphicsTextItem() {
  qDebug() << __FUNCTION__;
  setParentItem( parent );
}

SceneItem_LabelEditor::~SceneItem_LabelEditor() {
  qDebug() << __FUNCTION__;
}

void SceneItem_LabelEditor::focusInEvent( QFocusEvent *event ) {
  QGraphicsTextItem::focusInEvent( event );
}

void SceneItem_LabelEditor::focusOutEvent( QFocusEvent *event ) {
  QGraphicsTextItem::focusOutEvent( event );
  SceneItem_ConnectionHandle* h;
  SceneItem_Node* w;
  SceneItem_Connection* z;

  if ( parentItem() != NULL ) {
    switch ( parentItem()->type() ) {
    case SceneItem_ConnectionHandleType:
      h = ( SceneItem_ConnectionHandle* )parentItem();
      z = ( SceneItem_Connection* )h->parentItem();
      (( GraphicsScene* )scene() )->setData( z->index, toPlainText(), customRole::SymbolIndexRole );
      break;
    case SceneItem_NodeType:
      w = ( SceneItem_Node* )parentItem();
      (( GraphicsScene* )scene() )->setData( w->index, toPlainText(), customRole::CustomLabelRole );
      break;
    default:
      qDebug() << __FUNCTION__ << "ERROR, case not handled yet";
      break;
    }
  }
  scene()->removeItem( this );
  delete this;
}

int SceneItem_LabelEditor::type() const {
  return SceneItem_LabelEditorType;
}
