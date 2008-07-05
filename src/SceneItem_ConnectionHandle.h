//
// C++ Interface: SceneItem_ConnectionHandle
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SCENEITEM_CONNECTIONHANDLE_H
#define SCENEITEM_CONNECTIONHANDLE_H

/**
  @author Joachim Schiele <js@lastlog.de>
 */

#include <QGraphicsItem>
#include <QPointF>
#include <QPainter>
#include <QColor>
#include <QPen>
#include <QDebug>
#include <QTextDocument>
#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include "SceneItem_Connection.h"
#include "SceneItem_LabelEditor.h"

/**
  @author Joachim Schiele <js@lastlog.de>
 */
class SceneItem_ConnectionHandle : /*public QObject,*/ public QGraphicsItem {
//   Q_OBJECT
  friend class SceneItem_ConnectionLabel;
  public:
    SceneItem_ConnectionHandle();
    ~SceneItem_ConnectionHandle();
    void setLabel(QString label);
    int type() const;
  protected:
    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mousePressEvent ( QGraphicsSceneMouseEvent * event );
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );
    void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event );
    QVariant itemChange ( GraphicsItemChange change, const QVariant & value );
    void contextMenuEvent ( QGraphicsSceneContextMenuEvent * event );
  private:
    bool move_object_on_mouseMove;
    QString m_label;
    void addEditor();
/*  private slots:
    void removeConnectionSlot();
    void removeTransformationSlot();
    void editLabelSlot();*/
};

#endif
