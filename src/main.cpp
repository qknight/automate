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
 * \section concepts Concepts
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

 * @image html graphicsView2.jpg
 * @image html graphicsView3.jpg
 * @image html graphicsView4.jpg
 * @image html graphicsView5.jpg
 * @image html graphicsView6.jpg
 * @image html graphicsView7.jpg
 * @image html graphicsView8.jpg
 * @image html graphicsView9.jpg
 * @image html graphicsView10.jpg
 * @image html graphicsView11.jpg
 * @image html graphicsView12.jpg
 * @image html graphicsView13.jpg
 * @image html graphicsView14.jpg
 * @image html graphicsView15.jpg
 * @image html graphicsView16.jpg
 * @image html graphicsView17.jpg
 * @image html graphicsView18.jpg
 * @image html graphicsView19.jpg
 * @image html graphicsView20.jpg
 * @image html graphicsView21.jpg
 * @image html graphicsView22.jpg
 * @image html graphicsView22b.jpg
 * @image html graphicsView23.jpg
 * the picture below shows a directed graph without arrows using cubicTo bezier curve
 * i did not find out how to draw the arrow head to the right position so i
 * did not use the bezier approach which is said.
 * @image html images/graphicsView24.jpg
 * the picture below shows the 'current' state
 * @image html images/graphicsView25.jpg
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
