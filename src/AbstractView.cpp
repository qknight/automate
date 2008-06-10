//
// C++ Implementation: AbstractView
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "AbstractView.h"

AbstractView::AbstractView( QMainWindow *parent ) : QMainWindow( parent ) {}

AbstractView::~AbstractView() { }

void AbstractView::showWithFocus() {
  raise();
  //TODO problem: except the main widget all others seem to raise but NOT to focus
  //     this could be due to a kde overwrite here, which i didn't test yet

//   setWindowState(windowState() & ~Qt::WindowMinimized | Qt::WindowActive);
//   setFocus();
//   hide();
//   show();
}
