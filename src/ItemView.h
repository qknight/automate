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

#ifndef ITEMVIEW_H
#define ITEMVIEW_H

#include <QAbstractItemView>
#include <QGraphicsView>
#include <QPersistentModelIndex>
#include <QDebug>
#include <QResizeEvent>
#include <QGLWidget>

#include "GraphicsScene.h"
#include "Model.h"

/**
 @author Joachim Schiele <js@lastlog.de>
*/
/*! this is the core part of the custom graphicsView which handles all the insert/delete/modify stuff */
class ItemView : public QAbstractItemView {
  Q_OBJECT
  public:
    /*! constructor */
    ItemView( QGraphicsView* view, GraphicsScene* scene, Model *model, QWidget * parent );
    /*! destructor */
    ~ItemView();
  private:
    /*! enabled/disables antialiasing rendering */
    bool want_antialiasing;
    /*! a QGraphicsScene can have several views in theory, we only have one but that can be extended later */
    QGraphicsView* view;
    /*! we only have one scene which this graphicsView should visualize */
    GraphicsScene* scene;
    /*! we only have one model which this graphicsView should visualize */
    Model *model;
    /*! this is the rect in which all items lie */
    QRect visualRect( const QModelIndex &index ) const ;
    /*! not used but must be implemented since we inherit from QAbstractItemView */
    void scrollTo( const QModelIndex &index, ScrollHint hint = EnsureVisible ) ;
    /*! not used but must be implemented since we inherit from QAbstractItemView */
    QModelIndex indexAt( const QPoint &point ) const ;
    /*! not used but must be implemented since we inherit from QAbstractItemView */
    QModelIndex moveCursor( CursorAction cursorAction, Qt::KeyboardModifiers modifiers ) ;
    /*! not used but must be implemented since we inherit from QAbstractItemView */
    int horizontalOffset() const ;
    /*! not used but must be implemented since we inherit from QAbstractItemView */
    int verticalOffset() const ;
    /*! not used but must be implemented since we inherit from QAbstractItemView */
    bool isIndexHidden( const QModelIndex &index ) const ;
    /*! not used but must be implemented since we inherit from QAbstractItemView */
    void setSelection( const QRect &rect, QItemSelectionModel::SelectionFlags command ) ;
    /*! not used but must be implemented since we inherit from QAbstractItemView */
    QRegion visualRegionForSelection( const QItemSelection &selection ) const ;

    /*! callback which is called by the model on item insertion operations */
    void rowsInserted( const QModelIndex & parent, int start, int end );
    /*! callback which is called by the model on item removal operations */
    void rowsAboutToBeRemoved( const QModelIndex & parent, int start, int end );
    /*! callback which is called by the model on item change operations */
    void dataChanged( const QModelIndex & , const QModelIndex & );
    /*! helper function to get all items between two items in a hierarchy
     ** we have to check all items between topLeft and bottomRight
     ** let's update all QModelIndex'es in between */
    QModelIndex traverseTroughIndexes( QModelIndex index );
  public slots:
    /*! helper slot for renderHints */
    void toggleRenderHints();
  protected slots:
    /*! helper function to implement a reset call for a custom view, see implementation */
    void reset();
    /*! helper function to implement a layoutChanged call for a custom view, not implemented yet */
    void layoutChanged();
    /*! in a new view this will query all data to create a layout and to have all items in the scene */
    void init();
  signals:
    /*! helper signal for reset() call */
    void clearScene();
};

#endif
