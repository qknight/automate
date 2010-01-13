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
    virtual ~AbstractView();
  protected slots:
    /*! unhide the hidden widget and focus it, but doesn't work right now */
    void showWithFocus();
};

#endif
