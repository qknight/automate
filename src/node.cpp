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

#include "node.h"

node::node( AbstractTreeItem* parent ) : AbstractTreeItem( parent ) {
  ID = generateUniqueID( getObjectType() );
//   qDebug() << "NODE ID=" << ID << " TYPE=" << NODE;
}

node::~node() {
//   qDebug() << "~node()";
//   if ( childItems.size() > 0 )
//     qDebug() << "Warning, still have " << childItems.size() << " childItems";
//   if ( reverseChildItems.size() > 0 )
//     qDebug() << "Warning, still have " << reverseChildItems.size() << " reverseChildItems";
  qDeleteAll( reverseChildItems );
}

void node::dump() {
  qDebug() << "  \\---node::ID=" << ID << " childs:" << childCount() << ": " << ( unsigned int ) this << " parent=(" << ( unsigned int ) this->parent() << ")";
  // call dump for all children

  qDebug() << "     |-forward childs";
  for ( int i = 0; i < childCount(); ++i ) {
    child( i )->dump();
  }

  qDebug() << "     |-backward childs";
  for ( int i = 0; i < reverseChildItems.size(); ++i ) {
    reverseChildItems[i]->dump();
  }
}

unsigned int node::getObjectType() {
  return NODE;
}

void node::appendChild( AbstractTreeItem *item ) {
  if ( item->parent() != this ) {
    qDebug( "ERROR: you can't add a child to a parent item where \
            the parent of the child doesn't match the parent you want to add it to!" );
    return;
  }

  // this is the inverted connection item: r_item
  node_connection* f_item = static_cast<node_connection*>( item );
  node_connection* r_item = new node_connection( f_item->next_node );
  r_item->next_node = this;
  r_item->symbol_index = f_item->symbol_index;

  node* dst = static_cast<node*>( f_item->next_node );

  f_item->inverseConnectionId = r_item->getId();
  r_item->inverseConnectionId = f_item->getId();
  dst->appendChildReversePath( r_item );
  appendChildForwardPath( f_item );
}

void node::appendChildForwardPath( AbstractTreeItem *item ) {
  if ( childItems.contains( item ) ) {
    qDebug( "ERROR: detected an attepmt to add an already existing child!" );
    return;
  }
  childItems.append( item );
}

void node::appendChildReversePath( AbstractTreeItem *r_item ) {
  //TODO symbol needs to be set as well
  if ( reverseChildItems.contains( r_item ) ) {
    qDebug( "ERROR: detected an attepmt to add an already existing reverseChild!" );
    return;
  }

  reverseChildItems.append( r_item );
}

void node::removeChild( unsigned int index ) {
  childItems.removeAt( index );
}

unsigned int node::generateUniqueID( unsigned int a ) {
  return parentItem->generateUniqueID( a );
}
