//
// C++ Interface: SceneItem_LabelEditor
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SCENEITEM_CONNECTIONLABEL_H
#define SCENEITEM_CONNECTIONLABEL_H

/**
  @author Joachim Schiele <js@lastlog.de>
 */

#include <QGraphicsTextItem>
#include <QPointF>
#include <QPainter>
#include <QColor>
#include <QPen>
#include <QDebug>
#include <QTextDocument>
#include <QTextCursor>

#include "SceneItem_Connection.h"
#include "SceneItem_ConnectionHandle.h"

class SceneItem_ConnectionHandle;

/**
  @author Joachim Schiele <js@lastlog.de>
 */
class SceneItem_LabelEditor : public QGraphicsTextItem {
  public:
    SceneItem_LabelEditor( SceneItem_ConnectionHandle* parent );
    ~SceneItem_LabelEditor();
  private:
    SceneItem_ConnectionHandle* parent;
    QTextDocument* d;
    void focusInEvent( QFocusEvent *event );
    void focusOutEvent( QFocusEvent *event );
//     QVariant itemChange ( GraphicsItemChange change, const QVariant & value );
};

#endif
