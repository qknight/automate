//
// C++ Interface: SceneItem_FlexibleConnection
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SCENEITEM_FLEXIBLECONNECTION_H
#define SCENEITEM_FLEXIBLECONNECTION_H

#include <QGraphicsItem>
#include <QPainterPath>
#include <QPointF>
#include <QPainter>
#include <QColor>
#include <QPen>
#include <QGraphicsScene>

#include "ScneItem_FlexibleHandle.h"

namespace handleType {
enum itemType {
  start = 65536 + 1,
  start_handle,
  intermediate,
  end_handle,
  end
};
}

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class SceneItem_FlexibleConnection : public QGraphicsItem {
public:
  SceneItem_FlexibleConnection(QGraphicsScene* scene);
    ~SceneItem_FlexibleConnection();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void handleChanged(QPointF newpos, int t);
  private:
    QPointF start;
    QPointF intermediate;
    QPointF end;
    QPointF start_handle;
    QPointF end_handle;
    QGraphicsItem* addHandle(handleType::itemType type, QGraphicsItem* h);
    QGraphicsScene* m_scene;
    void forcedHandlePosUpdate(QPointF p, int type);
};

#endif
