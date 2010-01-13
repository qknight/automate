/*
    This file is part of automate.
      Copyright Joachim Schiele
      
    automate is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License.

    automate is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with automate.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
  @author Joachim Schiele <js@lastlog.de>
*/

#ifndef SCENEITEM_CONNECTIONHANDLE_H
#define SCENEITEM_CONNECTIONHANDLE_H

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

/*!
** This class represents a QGraphicsItem used to draw the 'connection handle' 
** between two nodes (SceneItem_Node). It can host an editor to change the label
** drawn in a gray bubble.
*/
class SceneItem_ConnectionHandle : public QObject, public QGraphicsItem {
  Q_OBJECT
  friend class SceneItem_ConnectionLabel;
  public:
    /*! constructor */
    SceneItem_ConnectionHandle();
    /*! destructor */
    ~SceneItem_ConnectionHandle();
    /*! sets a new label as '0', '1' or 'a' ... for this connection */
    void setLabel(QString label);
    /*! returns a type identifier that this is a connection, see code */
    int type() const;
  protected:
    /*! see the Qt docs about QGraphicsItem*/
    QPainterPath shape() const;
    /*! see the Qt docs about QGraphicsItem*/
    QRectF boundingRect() const;
    /*! see the Qt docs about QGraphicsItem*/
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    /*! complex overloading for usability tweaking */
    void mousePressEvent ( QGraphicsSceneMouseEvent * event );
    /*! complex overloading for usability tweaking */
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
    /*! complex overloading for usability tweaking */
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );
    /*! complex overloading for usability tweaking */
    void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event );
    /*! when this object is moved we need to call the parent to notify this since the connection
    ** has to be drawn differently now. */
    QVariant itemChange ( GraphicsItemChange change, const QVariant & value );
    /*! used for 'remove custom transformation' right now but other use cases as delete connection
    ** could be implemented */
    void contextMenuEvent ( QGraphicsSceneContextMenuEvent * event );
  private:
    /*! internal variable, is used to track if an item is moved with mousePressEvent/mouseReleaseEvent */
    bool move_object_on_mouseMove;
    /*! internal variable, is used to find out if a single click was made or a single move click was made */
    bool move_object_on_mouseMove_used;
    /*! caches the labelItems label as '0', '1' or all other QStrings. updated when updateData() is called */
    QString m_label;
    /*! adds the labelEditor which is an inline editor for editing the label*/
    void addEditor(QGraphicsSceneMouseEvent * event);
  private slots:
    //     void removeConnectionSlot();
    /*! removes the custom transformation of a connection and readds it to the autoLayout */
    void removeTransformationSlot();
    /*! used to edit the label with the inline labelEditor */
    void editLabelSlot();
};

#endif
