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
  friend class SceneItem_ConnectionHandle;
  public:
    SceneItem_LabelEditor(QGraphicsItem* parent);
    ~SceneItem_LabelEditor();
    int type() const;
  private:
    QTextDocument* d;
    void focusInEvent( QFocusEvent *event );
    void focusOutEvent( QFocusEvent *event );
};

#endif
