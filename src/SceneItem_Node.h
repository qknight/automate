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
// C++ Interface: SceneItem_Node
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SCENEITEM_NODE_H
#define SCENEITEM_NODE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QPainterPath>
#include <QPersistentModelIndex>
#include <QGraphicsView>
#include <QMenu>
#include <QGraphicsSceneMouseEvent>

#include "GraphicsScene.h"
#include "SceneItem_Connection.h"
#include "SceneItem_Types.h"

class SceneItem_Connection;
/**
 @author Joachim Schiele <js@lastlog.de>
*/
class SceneItem_Node : public QGraphicsItem {
  public:
    SceneItem_Node( QPersistentModelIndex index );
    ~SceneItem_Node();
    void addConnection( SceneItem_Connection* ci );
    int type() const;
    void updateData();
    QPersistentModelIndex index;
  private:
    void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event );
    QPainterPath shape() const;
    void removeConnection( SceneItem_Connection* ci );
    void hoverEnterEvent( QGraphicsSceneHoverEvent * event );
    void hoverLeaveEvent( QGraphicsSceneHoverEvent * event );
    QRectF boundingRect() const;
    QList<SceneItem_Connection *> ConnectionItems;
    QString label;
    bool start;
    bool final;
    bool hovering;
    int r; /*radius*/
    qreal penWidth;

    void contextMenuEvent( QGraphicsSceneContextMenuEvent * event );
  protected:
    QVariant itemChange( GraphicsItemChange change, const QVariant &value );
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
};

#endif
