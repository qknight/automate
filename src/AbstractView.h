//
// C++ Interface: AbstractView
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

// #include <QDialog>
#include <QMainWindow>
#include <QDebug>

/**
  @author Joachim Schiele <js@lastlog.de>
*/

/*! Handles views in a unique fashion.
No more duplicated code for handling all kind of views on program close.
*/
class AbstractView : public QMainWindow {
  friend class viewHandler;
  friend class automate;
    Q_OBJECT
  protected:
    AbstractView( QMainWindow *parent = 0 );
    ~AbstractView();
  protected slots:
    void showWithFocus();
};

#endif
