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

#include "SceneItem_LabelEditor.h"

// http://lists.trolltech.com/qt-interest/2007-03/thread00929-0.html
SceneItem_LabelEditor::SceneItem_LabelEditor( QGraphicsItem* parent ) : QGraphicsTextItem() {
//   qDebug() << __FUNCTION__;
  setParentItem( parent );
  connect( document(), SIGNAL( contentsChange( int, int, int ) ),
           this, SLOT( textEdited( int, int, int ) ) );
}

SceneItem_LabelEditor::~SceneItem_LabelEditor() {
//   qDebug() << __FUNCTION__;
}

void SceneItem_LabelEditor::focusOutEvent( QFocusEvent *event ) {
  QGraphicsTextItem::focusOutEvent( event );
  editingFinised();
  this->deleteLater();
}

void SceneItem_LabelEditor::textEdited( int /*position*/, int /*charsRemoved*/, int /*charsAdded*/ ) {
  if ( toPlainText().contains( "\n" ) )
    editingFinised();
}

void SceneItem_LabelEditor::editingFinised() {
  SceneItem_ConnectionHandle* h;
  SceneItem_Node* w;
  SceneItem_Connection* z;

  QString text = toPlainText().split( "\n" ).first();

  if ( parentItem() != NULL ) {
    switch ( parentItem()->type() ) {
    case SceneItem_ConnectionHandleType:
      h = ( SceneItem_ConnectionHandle* )parentItem();
      z = ( SceneItem_Connection* )h->parentItem();
      if ( text != "" )
        (( GraphicsScene* )scene() )->setData( z->index, text, customRole::SymbolIndexRole );
      break;
    case SceneItem_NodeType:
      w = ( SceneItem_Node* )parentItem();
      if ( text != "" )
        (( GraphicsScene* )scene() )->setData( w->index, text, customRole::CustomLabelRole );
      break;
    default:
      qDebug() << __FUNCTION__ << "ERROR, case not handled yet";
      break;
    }
    this->deleteLater();
  }
}

int SceneItem_LabelEditor::type() const {
  return SceneItem_LabelEditorType;
}



