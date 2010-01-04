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

#include "AutomateRoot.h"
#include "node.h"

AutomateRoot::AutomateRoot( AbstractTreeItem* parent ) : AbstractTreeItem( parent ) {
//   qDebug() << "adding a new AutomateRoot with parent: " << parent;
  objCnt_node = new objectCounter;
  objCnt_automateroot = new objectCounter;
  objCnt_nodeconnection = new objectCounter;
  ID = generateUniqueID( getObjectType() );
//   qDebug() << "NODE ID=" << ID << " TYPE=" << NODE;

  /*  qDebug() << setSymbol("foo");
  qDebug() << setSymbol("foo1");
  qDebug() << setSymbol("foo");
  qDebug() << setSymbol("foo2");
  dump();*/
}

AutomateRoot::~AutomateRoot() {
//   qDebug() << __PRETTY_FUNCTION__;
  delete objCnt_node;
  delete objCnt_automateroot;
  delete objCnt_nodeconnection;
  if (childCount() != 0) {
    qDebug() << __PRETTY_FUNCTION__ << "-> FATAL ERROR: not all child items were removed prior to this function call, exiting";
    exit(0);
  }
}

void AutomateRoot::dump() {
//   qDebug() << "automateroot::ID=" << ID << " -> " << childCount() << ": " << ( unsigned int ) this;
  // call dump for all children
  for ( int i = 0; i < childCount(); ++i ) {
    child( i )->dump();
  }
}

unsigned int AutomateRoot::getObjectType() {
  return AUTOMATE_ROOT;
}

void AutomateRoot::removeChild( unsigned int index ) {
  if ( (unsigned int)m_childItems.size() < index ) {
    qDebug() << "Fatal error, childItems.size() < index!";
    qDebug() << "having " << m_childItems.size() << " childs";
    exit( 0 );
  }
  AbstractTreeItem* child = m_childItems[index];
  m_childItems.removeAt( index );
  delete child;
}

unsigned int AutomateRoot::generateUniqueID( unsigned int a ) {
  /*
  ** the identifiers are used to label the objects in the graphicsView
  ** in general they are not used to access a object, there we still use either pointers
  ** or QModelIndexes

  ** This code is very important because it helps to get unique identifiers per object
  ** among the objects hierarchy. say nodes: n1 and n2 have index 1 and 2 BUT
  ** there can be node_connection1 and node_connection2 which also have index 1 and 2
  ** in general this improves use&feel because items are now numbered ascending in their
  ** occurance as the use would expect it.
  */
  unsigned int value;
  switch ( a ) {
  case AUTOMATE_ROOT:
    value = objCnt_automateroot->newID();
//         qDebug() << "AUTOMATE_ROOT::" << value;
    return value;
  case NODE:
    value = objCnt_node->newID();
//         qDebug() << "NODE::" << value;
    return value;
  case NODE_CONNECTION:
    value = objCnt_nodeconnection->newID();
//         qDebug() << "NODE_CONNECTION::" << value;
    return value;
  default:
    qDebug( "ERROR generateUniqueID failed because no case matched" );
    exit( 0 );
  }
}
