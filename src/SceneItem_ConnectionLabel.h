//
// C++ Interface: SceneItem_ConnectionLabel
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

#include <QGraphicsTextItem>
#include <QPointF>
#include <QPainter>
#include <QColor>
#include <QPen>
#include <QDebug>
#include <QTextDocument>
// #include <QString>

#include "SceneItem_Connection.h"

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class SceneItem_ConnectionLabel : public QGraphicsTextItem {
  public:
    SceneItem_ConnectionLabel();
    ~SceneItem_ConnectionLabel();
    void setLabel(QString label);
  protected:
    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
//     void focusInEvent(QFocusEvent *event);
//     void focusOutEvent(QFocusEvent *event);
    void mousePressEvent ( QGraphicsSceneMouseEvent * event );
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );
    void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event );
    QVariant itemChange ( GraphicsItemChange change, const QVariant & value );
//     QVariant itemChange ( GraphicsItemChange change, const QVariant & value );
  private:
    bool move_object_on_mouseMove;
    QTextDocument * d;
    QString m_label;
};

#endif
