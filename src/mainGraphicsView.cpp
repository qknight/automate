#include "mainGraphicsView.h"

mainGraphicsView::mainGraphicsView( Model *model, QDialog* parent ) : AbstractView( parent ) {
  this->model = model;
  view = new QGraphicsView;
//   view->setSizePolicy( QSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored) );

  //QGLWidget* view = new QGLWidget ;
  textBrowser = new QTextBrowser;
  itemView = new ItemView( view, model );

  QSplitter *splitter = new QSplitter;
  splitter->addWidget( textBrowser );
  splitter->addWidget( view );
  splitter->setStretchFactor( 0, 0 );
  splitter->setStretchFactor( 1, 1 );

  QGridLayout* layout = new QGridLayout( this );
  QToolBar* tb = new QToolBar("title", this);
  QAction* a = new QAction(QIcon(":/icons/node.png"),"test", this);
  tb->addAction(a);
  tb->addSeparator();

  tb->setMovable(true);
//   tb->setAllowedAreas ();

  layout->addWidget(tb);
  layout->addWidget( splitter );
  setLayout( layout );

  QItemSelectionModel *selectionModel = new QItemSelectionModel( model );
  itemView->setSelectionModel( selectionModel );

  /* debug code, TODO remove later */
  QString f;
  QTextStream o( &f );
  for ( int i = 0; i < model->rowCount( QModelIndex() ); ++i ) {
    if ( i == 0 )
      o << "graph with " << model->rowCount( QModelIndex() ) << " rows" << "\n";
    o << " |- child with " << model->rowCount( model->index( i, 0, QModelIndex() ) ) << " rows" << "\n";
  }
  gDebug( f );
  resize( 1024, 600 );
}

mainGraphicsView::~mainGraphicsView() {
}

void mainGraphicsView::gDebug( QString input ) {
  textBrowser->append( input );
}
