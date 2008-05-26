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

#include "Model.h"
#include "AbstractView.h"
#include "ItemView.h"
// #include "GraphicsView.h"

/*
** This class is responsible for displaying the graph as graphical representation
**  it makes use of a QAbstractItemView and a QGraphicsScene
*/
class mainGraphicsView : public AbstractView { /*, public Ui::mainGraphicsViewWidget*/
    Q_OBJECT
  public:
    mainGraphicsView( Model *, QDialog* parent = 0 );
    ~mainGraphicsView();
  private:
    void gDebug( QString input );
    ItemView* itemView;
    Model *model;
    QGraphicsView* view;
    QTextBrowser* textBrowser;
    QGraphicsItemGroup* generateNode( bool start, bool final, QString label, QString name );
};

#endif
