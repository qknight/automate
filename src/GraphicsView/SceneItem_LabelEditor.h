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

#ifndef SCENEITEM_CONNECTIONLABEL_H
#define SCENEITEM_CONNECTIONLABEL_H

#include <QGraphicsTextItem>
#include <QPointF>
#include <QPainter>
#include <QColor>
#include <QPen>
#include <QDebug>
#include <QTextDocument>
#include <QTextCursor>
#include <QRegExp>

#include "SceneItem_Connection.h"
#include "SceneItem_ConnectionHandle.h"

class SceneItem_ConnectionHandle;

/*! this is an inline editor for editing of a label on a connection as '0' or '1' are used for instance.
** since QString is used to represent the label there are quite a few possible labels...*/
class SceneItem_LabelEditor : public QGraphicsTextItem {
  Q_OBJECT
  friend class SceneItem_ConnectionHandle;
  public:
    /*! construcotr which is only called from either a node or a connection, parent must be set for the callback */
    SceneItem_LabelEditor(QGraphicsItem* parent);
    /*! this object is destructed after labelEditor use or when the view is deleted*/
    ~SceneItem_LabelEditor();
    /*! used to identify the type for internal use */
    int type() const;
  private:
    /*! temporary*/
    QTextDocument* d;
    /*! used to track when the item editing is finished */
    void focusOutEvent( QFocusEvent *event );
    /*! tracks when editing is finished from either focusOutEvent or pressing return */
    void editingFinised();
  private slots:
    /*! when the text editing is finished we get the modification details here */
    void textEdited ( int position, int charsRemoved, int charsAdded );
};

#endif
