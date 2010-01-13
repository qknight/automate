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
  model()->clear(); // removes childs in a recursive fasion
  // FIXME root->remove_all_items() or similar, before calling the destructor
  // this is important since the AutomateRoot should not remove any child items
  // in a recursive fashion. calling the ~AutomateRoot destructor should check
  // if all childs are gone, if not it should fail with a exit(0) call to indicate
  // a serious failure.
  // That said: remove all items [as nodes and node_connections] first via the model, 
  // next if all items are gone call the destructor of AutomateRoot which WILL NOT
  // FAIL then.
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
      view = new TreeView(model());
      a = QString("TreeView - %2").arg(name);
      view->setWindowTitle(a);
      view->show();
      break;
    case GraphicsViewType:
      view = new GraphicsView(model());
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



