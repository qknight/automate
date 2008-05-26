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

#include "node_connection.h"

node_connection::node_connection( AbstractTreeItem* parent ) : AbstractTreeItem( parent ) {
  ID = generateUniqueID( getObjectType() );
  next_node=parent;
  symbol_index=0;
  //   qDebug() << "NODE ID=" << ID << " TYPE=" << NODE;
}


void node_connection::dump() {
  qDebug() << "     |  \\---((node_connection " << ID /*<< "@" << (unsigned int) this*/ << "))" <<
//       parent()->getId() << "@" << (unsigned int)parent() <<
  " >> " << symbol_index << " >> DEST = " <<
  next_node->getId() /*<< "@" << (unsigned int)next_node*/;

  // call dump for all children
  if ( childCount() > 0 )
    qDebug() << "FATAL ERROR in" << __FILE__ << " " << __FUNCTION__ << "this should never happen";

  for ( int i = 0; i < childCount(); ++i ) {
    child( i )->dump();
  }
}

unsigned int node_connection::getObjectType() {
  return NODE_CONNECTION;
}

void node_connection::removeChild( unsigned int index ) {
  if ( childItems.size() < index ) {
    qDebug() << "Fatal error, childItems.size() < index!";
    qDebug() << "having " << childItems.size() << " childs";
    exit( 0 );
  }
  childItems.removeAt( index );
}

unsigned int node_connection::generateUniqueID( unsigned int a ) {
  return parentItem->generateUniqueID( a );
}
