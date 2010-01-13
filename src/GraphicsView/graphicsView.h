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

#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsPathItem>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QFontMetrics>
#include <QSplitter>
#include <QTableView>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QTextBrowser>
#include <QGraphicsView>
//#include <QGLWidget>
#include <QGridLayout>
#include <QSizePolicy>
#include <QToolBar>
#include <QAction>
#include <QStatusBar>
#include <QPoint>
#include <QCursor>

#include "Model.h"
#include "AbstractView.h"
#include "ItemView.h"
#include "GraphicsScene.h"
class GraphicsScene;
class ItemView;

/*!
 ** The graphicsView implements a graphical representation of the automate.
 ** The concept is to wrap QGraphicsView capabilities into a QAbstractItemView.
 **
 ** ItemView talks to the model and is called by the model.
 ** The QGraphicsScene inherited by GraphicsScene is what is used to display the
 ** data through ItemView. The GraphicsScene has another layer of items, namely:
 ** QGraphicsItems 
 **   HINT: this has nothing to do with a QGraphicsView (we don't inherit it)
 */
class GraphicsView : public AbstractView {
    Q_OBJECT
  public:
    /*! constructor, needs a model for operation */
    GraphicsView( Model *, QMainWindow* parent = 0 );
    /*! destructor */
    ~GraphicsView();
    /*! not used, but can be done later ... */
    QStatusBar* sb;
    /*! when using the shortcut to add a new node, the new node will be placed right under the cursor*/
    QPoint queryMouseCoordinatesOverQGraphicsView();
  private:
    /*! this is the scene we work with, there is only one (in opposite to views on a scene where you
    ** can have multiple views!) */
    GraphicsScene* scene;
    /*! the toolbar is used and filled with funky icons */
    QToolBar* tb;
    /*! the itemView is one of the core elements of our QGraphicsScene as QAbstractItemView backend */
    ItemView* itemView;
    /*! the model we work with, there is only one*/
    Model *model;
    /*! the view we use to visualize the scene */
    QGraphicsView* view;
    /*! a helper function to improve readability of the code */
    void populateMenu();
    /*!  */
    QItemSelectionModel *selectionModel;

  private Q_SLOTS:
    /*! insertNode this is one of two places where the graphical editor inserts nodes
    ** this place is the click on the left icon bar, we should insert the node somewhere in the
    ** views FoV since that makes sense. it does not sense to track the cursor since it is above
    ** the icon when this event happens */
    void insertNode();
    /*! zoomIn ...*/
    void zoomIn();
    /*! zoomOut ...*/
    void zoomOut();
    /*! zoomNormal zooms to 1:1 view */
    void zoomNormal();
    /*! not implemented yet but stubs are complete */
    void zoomFit();
    
    Q_SIGNALS:
    void insertNodeSignal(QPoint pos);
};

#endif
