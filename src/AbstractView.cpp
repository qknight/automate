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
  show();    // if the widget was clicked away using the [x] on the top right widget
  raise();   // if the widget is behind the main widget this will bring it to the foreground
  setFocus();// this does not work as expected
}
