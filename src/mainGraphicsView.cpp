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

#include "mainGraphicsView.h"

mainGraphicsView::mainGraphicsView( Model *model, QMainWindow* parent ) : AbstractView( parent ) {
  this->model = model;
  sb = new QStatusBar;
  view = new QGraphicsView;
  setWindowIcon(QIcon(QString::fromUtf8(":/icons/view_choose.png")));

  //QGLWidget* view = new QGLWidget ;
  scene = new GraphicsScene( model );
  itemView = new ItemView( view, scene, model, this );

  // we hide this widget since we only abuse it's connectivity for our QGraphicsScene/View
  itemView->hide();

  tb = new QToolBar("title", this);
  populateMenu();
  tb->setMovable(true);

  setCentralWidget(view);
  addToolBar(Qt::LeftToolBarArea, tb);
  setStatusBar(sb);

  QItemSelectionModel *selectionModel = new QItemSelectionModel( model );
  itemView->setSelectionModel( selectionModel );

  resize( 800, 600 );

  connect(scene,SIGNAL(zoomOut()), this, SLOT(zoomOut()));
  connect(scene,SIGNAL(zoomIn()), this, SLOT(zoomIn()));
  connect(scene,SIGNAL(zoomFit()), this, SLOT(zoomFit()));
  connect(scene, SIGNAL(hideView()), this, SLOT(hide()));
  connect(scene, SIGNAL(toggleRenderHints()), itemView, SLOT(toggleRenderHints()));
}

mainGraphicsView::~mainGraphicsView() {
//   qDebug() << __FUNCTION__;
  delete scene;
  delete view;
  delete sb;
}

void mainGraphicsView::populateMenu() {
  QAction* toggleStartAction = new QAction(QIcon(":/icons/startNode.png"),"'s' - start toggle", this);
  tb->addAction(toggleStartAction );
  connect(toggleStartAction , SIGNAL(triggered()), scene, SLOT(toggleStartEvent()));

  QAction* toggleFinalAction = new QAction(QIcon(":/icons/finalNode.png"),"'f' - final toggle", this);
  tb->addAction(toggleFinalAction);
  connect(toggleFinalAction, SIGNAL(triggered()), scene, SLOT(toggleFinalEvent()));

  tb->addSeparator();

  QAction* insertNodeAction = new QAction(QIcon(":/icons/bookmark_add.png"),"'n' - insert node", this);
  tb->addAction(insertNodeAction);
  connect(insertNodeAction , SIGNAL(triggered()), scene, SLOT(insertNode()));

  QAction* removeAction = new QAction(QIcon(":/icons/button_cancel.png"),"'x' - del node/connection", this);
  tb->addAction(removeAction );
  connect(removeAction , SIGNAL(triggered()), scene, SLOT(removeEvent()));

  tb->addSeparator();

  QAction* printAction = new QAction(QIcon(":/icons/printer2.png"),"'p' - Print", this);
  tb->addAction(printAction);
  connect(printAction, SIGNAL(triggered()), scene, SLOT(print()));

  tb->addSeparator();

  QAction* zoomInAction = new QAction(QIcon(":/icons/viewmag+.png"),"Zoom In '+'", this);
  tb->addAction(zoomInAction);
  connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));

  QAction* zoomOutAction = new QAction(QIcon(":/icons/viewmag-.png"),"Zoom Out '-'", this);
  tb->addAction(zoomOutAction);
  connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));

  QAction* zoomNormalAction = new QAction(QIcon(":/icons/viewmag1.png"),"Zoom Normal", this);
  tb->addAction(zoomNormalAction);
  connect(zoomNormalAction, SIGNAL(triggered()), this, SLOT(zoomNormal()));

  QAction* zoomFitAction = new QAction(QIcon(":/icons/viewmagfit.png"),"Zoom Fit '/'", this);
  tb->addAction(zoomFitAction);
  connect(zoomFitAction, SIGNAL(triggered()), this, SLOT(zoomFit()));

  tb->addSeparator();

  QAction* toggleHighlightAction = new QAction(QIcon(":/icons/highlighting.png"),"'h' - toggleHighlightAction", this);
  tb->addAction(toggleHighlightAction);
  connect(toggleHighlightAction, SIGNAL(triggered()), scene, SLOT(toggleHighlight()));

  QAction* toggleAntialiasingAction = new QAction(QIcon(":/icons/antialiasing.png"),"'t' - toggleAntialiasingAction", this);
  tb->addAction(toggleAntialiasingAction);
  connect(toggleAntialiasingAction, SIGNAL(triggered()), itemView, SLOT(toggleRenderHints()));

  QAction* toggleBoundingBoxAction = new QAction(QIcon(":/icons/boundingBox.png"),"'b' - toggleBoundingBoxAction", this);
  tb->addAction(toggleBoundingBoxAction);
  connect(toggleBoundingBoxAction, SIGNAL(triggered()), scene, SLOT(toggleBoundingBox()));

  QAction* toggleDrawItemShapeAction = new QAction(QIcon(":/icons/drawShape.png"),"'e' - toggleDrawItemShapeAction ", this);
  tb->addAction(toggleDrawItemShapeAction );
  connect(toggleDrawItemShapeAction, SIGNAL(triggered()), scene, SLOT(toggleDrawItemShape()));

  QAction* toggleColoredConnectionHelper = new QAction(QIcon(":/icons/coloredConnectionHelper.png"),"'l' - toggleColoredConnectionHelper ", this);
  tb->addAction(toggleColoredConnectionHelper );
  connect(toggleColoredConnectionHelper, SIGNAL(triggered()), scene, SLOT(toggle_coloredConnectionHelper()));

  tb->addSeparator();

  QAction* toggle_customNodeLabelsAction = new QAction(QIcon(":/icons/customNodeLabel.png"),"'?' - toggle_customNodeLabelsAction ", this);
  tb->addAction(toggle_customNodeLabelsAction );
  connect(toggle_customNodeLabelsAction, SIGNAL(triggered()), scene, SLOT(toggle_customNodeLabels()));

  QAction* toggle_customConnectionLabelsAction = new QAction(QIcon(":/icons/customConnectionLabel.png"),"'?' - toggle_customConnectionLabelsAction ", this);
  tb->addAction(toggle_customConnectionLabelsAction );
  connect(toggle_customConnectionLabelsAction, SIGNAL(triggered()), scene, SLOT(toggle_customConnectionLabels()));
}

void mainGraphicsView::zoomIn() {
  view->scale( 1.2, 1.2 );
}

void mainGraphicsView::zoomOut() {
  view->scale( 0.8, 0.8 );
}

void mainGraphicsView::zoomNormal() {
  view->resetMatrix();
}

void mainGraphicsView::zoomFit() {
  qDebug() << "FIXME zoomFit() not implemented yet";
  //FIXME put your code here
//   view->resetMatrix();
//   view->setSceneRect(scene->sceneRect());
}
