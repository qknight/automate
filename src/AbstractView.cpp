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
