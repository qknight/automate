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
#include <QGLWidget>
#include <QGridLayout>
#include <QSizePolicy>
#include <QToolBar>
#include <QAction>
#include <QStatusBar>

#include "Model.h"
#include "AbstractView.h"
#include "ItemView.h"

/*!
 ** The graphicsView implements a graphical representation of the automate.
 ** The concept is to wrap QGraphicsView capabilities into a QAbstractItemView.
 **
 ** ItemView is what talks to the model and what is called by the model.
 ** The QGraphicsScene inherited by GraphicsScene is what is used to display the
 ** data trough ItemView. The GraphicsScene has another layer of items, namely:
 ** QGraphicsItems.
 */
class graphicsView : public AbstractView {
    Q_OBJECT
  public:
    /*! constructor, needs a model for operation */
    graphicsView( Model *, QMainWindow* parent = 0 );
    /*! destructor */
    ~graphicsView();
    /*! not used, but can be done later ... */
    QStatusBar* sb;
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

  private slots:
    /*! zoomIn ...*/
    void zoomIn();
    /*! zoomOut ...*/
    void zoomOut();
    /*! zoomNormal zooms to 1:1 view */
    void zoomNormal();
    /*! not implemented yet but stubs are complete */
    void zoomFit();
};

#endif
