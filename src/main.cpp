// automate implements an automate class in c++ using qt4
// Copyright (C) 2007 Joachim Schiele
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// version 2 as published by the Free Software Foundation
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

/*! \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 *
 * This project can display/edit an automate NFA/DFA/epsilon-automate in two
 * different view concepts:
 *  - treeView: a hierarchical view concept which displays the data very efficiently
 *  - graphicsView: a rendered directed graph with nodes/edges.
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: download the tar file / git clone / svn co
 * \subsection step2 Step 2: make; qmake
 * \subsection step3 Step 3: cd debug; ./automate
 *
 * \section z Some screenshots taken fram the beginning of the developing process
 * <img src="../images/graphicsView2.jpg" alt="Screenshot-graphicsView2.jpg">
 * <img src="../images/graphicsView3.jpg" alt="Screenshot-graphicsView3.jpg">
 * <img src="../images/graphicsView4.jpg" alt="Screenshot-graphicsView4.jpg">
 * <img src="../images/graphicsView5.jpg" alt="Screenshot-graphicsView5.jpg">
 * <img src="../images/graphicsView6.jpg" alt="Screenshot-graphicsView6.jpg">
 * <img src="../images/graphicsView7.jpg" alt="Screenshot-graphicsView7.jpg">
 * <img src="../images/graphicsView8.jpg" alt="Screenshot-graphicsView8.jpg">
 * <img src="../images/graphicsView9.jpg" alt="Screenshot-graphicsView9.jpg">
 * <img src="../images/graphicsView10.jpg" alt="Screenshot-graphicsView10.jpg">
 * <img src="../images/graphicsView11.jpg" alt="Screenshot-graphicsView11.jpg">
 * <img src="../images/graphicsView12.jpg" alt="Screenshot-graphicsView12.jpg">
 * <img src="../images/graphicsView13.jpg" alt="Screenshot-graphicsView13.jpg">
 * <img src="../images/graphicsView14.jpg" alt="Screenshot-graphicsView14.jpg">
 * <img src="../images/graphicsView15.jpg" alt="Screenshot-graphicsView15.jpg">
 * <img src="../images/graphicsView16.jpg" alt="Screenshot-graphicsView16.jpg">
 * <img src="../images/graphicsView17.jpg" alt="Screenshot-graphicsView17.jpg">
 * <img src="../images/graphicsView18.jpg" alt="Screenshot-graphicsView18.jpg">
 * <img src="../images/graphicsView19.jpg" alt="Screenshot-graphicsView19.jpg">
 * <img src="../images/graphicsView20.jpg" alt="Screenshot-graphicsView20.jpg">
 * <img src="../images/graphicsView21.jpg" alt="Screenshot-graphicsView21.jpg">
 * <img src="../images/graphicsView22.jpg" alt="Screenshot-graphicsView22.jpg">
 * <img src="../images/graphicsView22b.jpg" alt="Screenshot-graphicsView22b.jpg">
 */

#include <QApplication>
#include "automatehandler.h"

int main( int argc, char* argv[] ) {
  QApplication app( argc, argv );
//   connect(&app,SIGNAL(lastWindowClosed()),&app,SLOT(quit()));
  automatehandler* z = new automatehandler();
  z->show();
  return app.exec();
}
