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

#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

// #include <QDialog>
#include <QMainWindow>
#include <QDebug>

/*! Handles views in a unique fashion.
No more duplicated code for handling all kind of views on program close. */
class AbstractView : public QMainWindow {
  friend class viewHandler;
  friend class automate;
    Q_OBJECT
  protected:
    /*! constructor */
    AbstractView( QMainWindow *parent = 0 );
    /*! destructor */
    ~AbstractView();
  protected slots:
    /*! unhide the hidden widget and focus it, but doesn't work right now */
    void showWithFocus();
};

#endif
