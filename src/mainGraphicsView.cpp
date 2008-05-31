#include "mainGraphicsView.h"

mainGraphicsView::mainGraphicsView( Model *model, QDialog* parent ) : AbstractView( parent ) {
  this->model = model;
  view = new QGraphicsView;
//   view->setSizePolicy( QSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored) );

  //QGLWidget* view = new QGLWidget ;
//   textBrowser = new QTextBrowser;
  itemView = new ItemView( view, model, this );
  itemView->hide(); // we hide this widget since we only abuse it's connectivity for our QGraphicsScene/View

  QSplitter *splitter = new QSplitter;
  splitter->addWidget( view );
//   splitter->setStretchFactor( 0, 0 );
//   splitter->setStretchFactor( 1, 1 );

  QGridLayout* layout = new QGridLayout( this );
  populateMenu();

  tb->setMovable(true);

  layout->addWidget(tb);
  layout->addWidget( splitter );
  setLayout( layout );

  QItemSelectionModel *selectionModel = new QItemSelectionModel( model );
  itemView->setSelectionModel( selectionModel );

  resize( 1024, 600 );
}

mainGraphicsView::~mainGraphicsView() { }

void mainGraphicsView::populateMenu() {
  tb = new QToolBar("title", this);
  QAction* a = new QAction(QIcon(":/icons/node.png"),"test", this);
  tb->addAction(a);
  tb->addSeparator();
}

