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
    graphicsView( Model *, QMainWindow* parent = 0 );
    ~graphicsView();
    QStatusBar* sb;
  private:
    GraphicsScene* scene;
    QToolBar* tb;
    ItemView* itemView;
    Model *model;
    QGraphicsView* view;
    void populateMenu();
    QGraphicsItemGroup* generateNode( bool start, bool final, QString label, QString name );

  private slots:
    void zoomIn();
    void zoomOut();
    void zoomNormal();
    void zoomFit();
};

#endif
