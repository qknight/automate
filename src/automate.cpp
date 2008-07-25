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


#include "automate.h"
// #define MODELTEST

automate::automate() {
  vh = new viewHandler;
  root = new AutomateRoot;
  m_model = new Model(automateRootPtr());
#ifdef MODELTEST
  modeltest = new ModelTest(m_model);
#endif

  // this will create a nice label for the automate
  QString date = QDate().currentDate().toString("yyyy MMMd");
  QString time = QTime().currentTime().toString("hh.mm.ss");
  name = QString("%1 - %2").arg(date).arg(time);
}

automate::~automate() {
//   qDebug() << "automate::~automate()";
  delete vh;
#ifdef MODELTEST
  delete modeltest;
#endif
  delete m_model;
  delete root;

}
AbstractTreeItem* automate::automateRootPtr() {
  return static_cast<AbstractTreeItem*>(root);
}

void automate::dump() {
  root->dump();
}

Model* automate::model() {
  return m_model;
}

void automate::openNewView(ViewType vt) {
  AbstractView* view;
  QString a;
//   qDebug() << "in file: " << __FILE__ << "on line: " << __LINE__;
  switch (vt) {
    case TreeViewType:
      view = new treeView(model());
      a = QString("TreeView - %2").arg(name);
      view->setWindowTitle(a);
      view->show();
      break;
    case GraphicsViewType:
      view = new graphicsView(model());
      a = QString("GraphicsView - %2").arg(name);
      view->setWindowTitle(a);
      view->show();
      break;
    default:
      qDebug() << "openNewView: error, case not handles";
      return;
  }
  vh->addHandle(view);
}

unsigned int automate::childCount(){
  return root->childCount();
}

unsigned int automate::connectionCount(){
  int a = 0;
  for (unsigned int i=0; i < childCount(); ++i) {
    a+=root->child(i)->childCount();
  }
  return a;
}

void automate::reset() {
  m_model->reset();
}

void automate::layoutChanged() {
  m_model->layoutChanged();
}



