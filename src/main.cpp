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

/*! \mainpage Sourcecode documentation of the automate classes
 *
 * \section intro_sec Introduction
 *
 * This project can display/edit an automate NFA/DFA/epsilon-automate in two
 * different view concepts:
 *  - treeView: a hierarchical view concept which displays the data very efficiently
 *  - graphicsView: a rendered directed graph with nodes/edges.
 * This project contains some other parts as well:
 *  - automate_algorithms.cpp features some algorithms which where written based on
 *    an 'now' outdate data structure but which wasn't ported to the current data structure
 *    anymore. If one needs to write functions as:
 *     - complete DFA : can't think of what that codes does, do you?
 *     - getAutomateType() : finds out what kind of lang we have: epsilon automate / NFA / DFA / ...
 *     - convert2NFA() : converts a epsilon automate to a NFA
 *     - convert2DFA() : converts a NFA or epsilon automate to a DFA
 *     - convert2miniDFA() : minimizes a DFA
 *
 * \section issues Issues
 * A list of current issues can be found in the TODO file. The CHANGELOG file was
 * introduced in the end of the project but would have been helpful in many cases.
 * The same goes for version control systems: we used svn but since svn needs a working
 * internet connection it's pretty useless for offline working. Using git made a fundamental
 * change in 'code change documentation'.
 *
 * If I would have to warn you of issues then I would say:
 *  - please read the TODO file carefully
 *  - QGraphicsItem is a nice concept but in the end the SceneItem_Connection should
 *    have been implemented as base class for:
 *      - a loop item
 *      - a normal connection item
 *    but as it isn't that way a lot of things cause problems hard to come along.
 *  - use and feel of the graphicsView is broken in some ways as selecting connections with
 *    clicking on it's labelItem isn't really what one wants since selection handling should
 *    be done differently (by selection the line which is the primary item and not it's labelItem).
 *    The problem is that this wasn't possible since when you have several loops it's very hard to
 *    click the right line.
 *  - QGraphicsItems should not derive QObject but it is not possible to use a contextMenu AND not
 *    to use a QObject based class.
 *  - the model code is very complex and the QGraphicsScene which is wrapped as a custom view trough
 *    the ItemView class makes it even more complex. Just keep in mind that a stack strace with gdb
 *    helps a lot to find out which function call functions you want to monitor.
 *
 * \section install_sec Installation
 * \subsection step1 Step 1: download the tar file / git clone / svn co
 * \subsection step2 Step 2: make; qmake
 * \subsection step3 Step 3: cd debug; ./automate
 *
 * \section z Some screenshots taken fram the beginning of the developing process
 *  - these screenshots show many usability issues and in the end show the process to a working
 *    editing concept. some concepts where thrown away and others were never meant to be included
 *    but added here to show what can be done.
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
 * <img src="../images/graphicsView23.jpg" alt="Screenshot-graphicsView23.jpg">
 * <img src="../images/graphicsView24.jpg" alt="Screenshot-graphicsView24.jpg">
 * <img src="../images/graphicsView25.jpg" alt="Screenshot-graphicsView25.jpg">
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
