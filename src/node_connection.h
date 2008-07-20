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

#ifndef NODE_CONNECTION_H
#define NODE_CONNECTION_H

#include "AbstractTreeItem.h"
#include "node.h"

/*! A new connection is created with a invalid destination (NULL) and:
** - the destination can be changed as often as needed but
** - it can't be resetted to NULL
** - if a node is deleted all the connection references (in/out/loop) are removed
**   (see node.cpp for more detail)
** You can use the internal int representation of the literals Sigma used to express
** transitions (values on the edges) from one node to another (or loop). This is handy
** in case you want to compare values fast (instead of QString compare)
**
 ** inserting childs and removing childs is heavily modified in this class!
*/
class node_connection : public AbstractTreeItem {
  public:
    node_connection( AbstractTreeItem* parent );
    /*! WARNING: never delete objects as for instance childItems in the structure here
     ** since this will create inconsistencies between the model and this data structure.<br>
     ** A better way is to fail with exit(0) and a meaningful error message meant for
     ** developrs: since this problem must be handled with great care! */
    ~node_connection();
    AbstractTreeItem* next_node();
    void dump();
    void setNext_node( AbstractTreeItem* node );
    unsigned int getObjectType();
    unsigned int symbol_index();
    void setSymbol_index( unsigned int symbol_index );
    void removeChild( unsigned int index );
    node_connection* inverseConnection;
  private:
    unsigned int generateUniqueID( unsigned int );
    unsigned int m_symbol_index;
    AbstractTreeItem* m_next_node;
};

#endif


