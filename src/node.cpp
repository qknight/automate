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

// WARNING: never delete objects as for instance childItems in the structure here
// since this will create inconsistencies between the model and this data structure.
// A better way is to fail with exit(0) since this problem must be handled with great care!
node::~node() {
//   qDebug() << "~node()";
  if ( m_childItems.size() > 0 ) {
    qDebug() << "FATAL ERROR: Still have " << m_childItems.size() << " childItems";
    exit(0);
  }
  if ( m_reverseChildItems.size() > 0 ) {
    qDebug() << "FATAL ERROR: Still have " << m_reverseChildItems.size() << " reverseChildItems";
    exit(0);
  }
}

void node::dump() {
  qDebug() << "  \\---node::ID=" << ID << " childs:" << childCount() << ": " << ( unsigned int ) this << " parent=(" << ( unsigned int ) this->parent() << ")";
  // call dump for all children

  qDebug() << "     |-forward childs";
  for ( int i = 0; i < childCount(); ++i ) {
    child( i )->dump();
  }

  qDebug() << "     |-backward childs";
  for ( int i = 0; i < reverseChildItems().size(); ++i ) {
    reverseChildItems()[i]->dump();
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
  node_connection* r_item = new node_connection( f_item->next_node() );
  r_item->setNext_node(this);
  r_item->symbol_index = f_item->symbol_index;

  node* dst = static_cast<node*>( f_item->next_node() );

  f_item->inverseConnection = r_item;
  r_item->inverseConnection = f_item;
  dst->appendChildReversePath( r_item );
  appendChildForwardPath( f_item );
}

void node::removeChild( unsigned int index ) {
  // 1. first delete the reverse connection
  node_connection* f_item = ((node_connection*)m_childItems[index]);
  node_connection* r_item = f_item->inverseConnection;
//   qDebug() << (unsigned int)f_item->inverseConnection;
//   qDebug() << (unsigned int)r_item->inverseConnection;
//   ((node*)r_item->parent())->removeChildReversePath(r_item);

  AbstractTreeItem* rItem = r_item;//inverseConnection;
  AbstractTreeItem* rItemParent = rItem->parent();
  (( node* )rItemParent )->removeChildReversePath( rItem );

//   node_connection* f_item = ((node_connection*)m_childItems[index]);
//   node_connection* r_item = f_item->inverseConnection;
//   ((node*)r_item->parent())->removeChildReversePath(r_item);

  // 2. now finally delete the forward connection
  m_childItems.removeAt( index );
}

void node::appendChildForwardPath( AbstractTreeItem *item ) {
  if ( m_childItems.contains( item ) ) {
    qDebug( "ERROR: detected an attepmt to add an already existing child!" );
    return;
  }
  m_childItems.append( item );
}

void node::appendChildReversePath( AbstractTreeItem *r_item ) {
  //TODO symbol needs to be set as well
  if ( m_reverseChildItems.contains( r_item ) ) {
    qDebug( "ERROR: detected an attepmt to add an already existing reverseChild!" );
    return;
  }

  m_reverseChildItems.append( r_item );
}

void node::removeChildReversePath( AbstractTreeItem *item ){
  for(int i=0; i < m_reverseChildItems.size(); ++i)
    if (item == m_reverseChildItems[i]) {
//       qDebug() << (unsigned int) this << "Item to delete found";
      m_reverseChildItems.removeAt(i);
      return;
    }
//     qDebug() << (unsigned int) this <<  "Item to delete NOT found";
}

unsigned int node::generateUniqueID( unsigned int a ) {
  return parentItem->generateUniqueID( a );
}

const QList<AbstractTreeItem*> node::reverseChildItems() {
  return m_reverseChildItems;
}


