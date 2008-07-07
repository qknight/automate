/****************************************************************************
**
** Copyright (C) 2007-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.0, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** In addition, as a special exception, Trolltech, as the sole copyright
** holder for Qt Designer, grants users of the Qt/Eclipse Integration
** plug-in the right for the Qt/Eclipse Integration to link to
** functionality provided by Qt Designer and its related libraries.
**
** Trolltech reserves all rights not expressly granted herein.
**
** Trolltech ASA (c) 2007
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

//
// C++ Interface: SceneItem_Connection
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SCENEITEM_CONNECTION_H
#define SCENEITEM_CONNECTION_H

#include <QGraphicsItem>
#include <QPersistentModelIndex>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QRectF>
#include <QPainterPath>
#include <QtGui>
#include <math.h>

#include "SceneItem_Node.h"
#include "SceneItem_Types.h"
#include "SceneItem_ConnectionHandle.h"

#define CIRCLE_FOR_SYNBOL_RADIUS 14
#define MAX_BRUSH_SIZE 8

class SceneItem_Node;
class SceneItem_ConnectionHandle;

class SceneItem_Connection : public QGraphicsItem {
  friend class SceneItem_ConnectionHandle;
  public:
    SceneItem_Connection( QPersistentModelIndex index );
    ~SceneItem_Connection();
    void updateData();
    QRectF boundingRect() const;
    SceneItem_Node *startItem() const {
      return myStartItem;
    }
    SceneItem_Node *endItem() const {
      return myEndItem;
    }
    void updatePosition();
    int type() const;
    void highlight( bool status );
    void labelItemPositionCallback( const QPointF& oldPos, const QPointF& newPos );
    bool customTransformation();
    bool isLoop();
    void setAutoLayoutFactor(qreal factor);
    QPersistentModelIndex index;
  protected:
    void setCustomTransformation(bool value);
    QString label;
    bool m_highlight;
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
    QPainterPath shape() const;
  private:
    bool m_customTransformation;
    qreal ooffset;
    qreal poffset;
    QPainterPath connectionPath() const;
    void updateLabelPosition();
    SceneItem_ConnectionHandle* labelItem;
    void hoverEnterEvent( QGraphicsSceneHoverEvent * event );
    void hoverLeaveEvent( QGraphicsSceneHoverEvent * event );
    QLineF createLine( QPointF a, QPointF b );
    QPolygonF arrowHead;
    QPen pen;
    void setColor( const QColor &color ) {
      myColor = color;
    }
    QColor m_color;
    SceneItem_Node *myStartItem;
    SceneItem_Node *myEndItem;
    QColor myColor;
    QLineF line;
};

#endif
