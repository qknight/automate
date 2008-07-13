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
  m_next_node = NULL;
  inverseConnection = NULL;

  setSymbol_index( 0 );
  //   qDebug() << "NODE ID=" << ID << " TYPE=" << NODE;
}

// WARNING: never delete objects as for instance childItems in the structure here
// since this will create inconsistencies between the model and this data structure.
// A better way is to fail with exit(0) since this problem must be handled with great care!
node_connection::~node_connection() {
//   qDebug() << __FUNCTION__;
}

void node_connection::dump() {
  QString m_next_node_Id;
  if(m_next_node != NULL)
    m_next_node_Id = QString("n%1").arg(m_next_node->getId());
  else
    m_next_node_Id = "next_node is not set";
  //FIXME check m_next_node for NULL
  qDebug() << "     |  \\---((node_connection " << ID /*<< "@" << (unsigned int) this*/ << "))" <<
//       parent()->getId() << "@" << (unsigned int)parent() <<
  " >> " << symbol_index() << " >> DEST = " <<
  m_next_node_Id <<
  "inverseConnection =" << QString("c%1").arg(inverseConnection->getId());

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
  if (( unsigned int )m_childItems.size() < index ) {
    qDebug() << "Fatal error, childItems.size() < index!";
    qDebug() << "having " << m_childItems.size() << " childs";
    exit( 0 );
  }
  m_childItems.removeAt( index );
}

unsigned int node_connection::generateUniqueID( unsigned int a ) {
  return parentItem->generateUniqueID( a );
}

AbstractTreeItem* node_connection::next_node() {
  return m_next_node;
}

void node_connection::setNext_node( AbstractTreeItem* newNextNode ) {
  if ( m_next_node == newNextNode )
    return;
//   qDebug() << "warning: we have to relocate the reverseconnection as well";

  if ( inverseConnection == NULL ) {
    m_next_node = newNextNode;
    return;
  }
  // 1. remove the m_next_node's reverse connection reference (remove the reverse connection)
  AbstractTreeItem* rItem = inverseConnection;
  AbstractTreeItem* rItemParent = rItem->parent();
  (( node* )rItemParent )->removeChildReversePath( rItem );

  // 2. next add the reverse connection
  (( node* )newNextNode )->appendChildReversePath( rItem );

  // 3. reset the parent entry
  rItem->setParent( newNextNode );

  // 4. overwrite current m_next_node with node
  m_next_node = newNextNode;
  return;
}

unsigned int node_connection::symbol_index() {
  return m_symbol_index;
}

void node_connection::setSymbol_index( unsigned int symbol_index ) {
  m_symbol_index = symbol_index;

  // this code holds te reverseconnection's data in sync
  if ( inverseConnection != NULL ) {
    if ( inverseConnection->symbol_index() != symbol_index )
      inverseConnection->setSymbol_index( symbol_index );
  }
}











