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

/*
** This class is responsible for displaying the graph as graphical representation
**  it makes use of a QAbstractItemView and a QGraphicsScene
*/
class mainGraphicsView : public AbstractView {
    Q_OBJECT
  public:
    mainGraphicsView( Model *, QMainWindow* parent = 0 );
    ~mainGraphicsView();
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
};

#endif
