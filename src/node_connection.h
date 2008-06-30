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

class node_connection : public AbstractTreeItem {
  public:
    node_connection( AbstractTreeItem* parent );
    ~node_connection();
    void dump();
    AbstractTreeItem* next_node();
    void setNext_node( AbstractTreeItem* node );
    unsigned int getObjectType();
    unsigned int symbol_index();
    void setSymbol_index( unsigned int symbol_index );
    void removeChild( unsigned int index );
    node_connection* inverseConnection;
  private:
    unsigned int m_symbol_index;
    AbstractTreeItem* m_next_node;
    unsigned int generateUniqueID( unsigned int );
};

#endif


