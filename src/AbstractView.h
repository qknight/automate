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
Handle views in a unique fashion.
No more duplicated code for handling all kind of views on program close.

  @author Joachim Schiele <js@lastlog.de>
*/
class AbstractView : public QMainWindow {
    Q_OBJECT
  public:
    AbstractView( QMainWindow *parent = 0 );
    ~AbstractView();
  public slots:
    void showWithFocus();
};

#endif
