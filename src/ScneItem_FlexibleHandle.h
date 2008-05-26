//
// C++ Interface: ScneItem_FlexibleHandle
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SCNEITEM_FLEXIBLEHANDLE_H
#define SCNEITEM_FLEXIBLEHANDLE_H

#include <QGraphicsItem>
#include <QPainterPath>
#include <QPointF>
#include <QPainter>
#include <QColor>
#include <QPen>
#include <QGraphicsScene>
#include <QDebug>

#include "SceneItem_FlexibleConnection.h"

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class ScneItem_FlexibleHandle : public QGraphicsItem
{
public:
    ScneItem_FlexibleHandle(int type);
    ~ScneItem_FlexibleHandle();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QVariant itemChange ( GraphicsItemChange change, const QVariant & value );
    int type () const;
    int m_type;
    void handleChanged(QPointF newpos, int t);
};

#endif
