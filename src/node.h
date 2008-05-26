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

#ifndef NODE__HH__
#define NODE__HH__

#include "AbstractTreeItem.h"
#include "node_connection.h"

class node : public AbstractTreeItem {
  public:
    node( AbstractTreeItem* parent );
    ~node();
    void dump();
    unsigned int getObjectType();
    void appendChild( AbstractTreeItem *child );
    void removeChild( unsigned int index );

    QList<AbstractTreeItem*> reverseChildItems;
  private:
    void appendChildForwardPath( AbstractTreeItem *item );
    void appendChildReversePath( AbstractTreeItem *item );
    unsigned int generateUniqueID( unsigned int );
};

#endif
