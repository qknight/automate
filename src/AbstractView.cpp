/*
    This file is part of automate.
      Copyright Joachim Schiele
      
    automate is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License.

    automate is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with automate.  If not, see <http://www.gnu.org/licenses/>.
*/

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
