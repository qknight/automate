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


#ifndef NODE__HH__
#define NODE__HH__

#include "AbstractTreeItem.h"
#include "node_connection.h"

#include <QPoint>

/*! a node represents 'a node' in the data */
class node : public AbstractTreeItem {
  friend class node_connection;
  public:
    node( AbstractTreeItem* parent );
    /*! WARNING: never delete objects as for instance childItems in the structure here
     ** since this will create inconsistencies between the model and this data structure.<br>
     ** A better way is to fail with exit(0) and a meaningful error message meant for
     ** developrs: since this problem must be handled with great care! */
    ~node();
    /*! dumps the internal state for debugging */
    void dump();
    /*! returns the object type which is used in the model for example */
    unsigned int getObjectType();
    /*! adds a child (a connection) but also adds a reverse child, see code since this is quite complex */
    void appendChild( AbstractTreeItem *child );
    /*! removes a child (a connection) but also removes a reverse child, see code since this is quite complex */
    void removeChild( unsigned int index );
    /*! returns the contents of m_reverseChildItems */
    const QList<AbstractTreeItem*> reverseChildItems();
  private:
    /*! generates a unic id by calling it's parent recursively */
    unsigned int generateUniqueID( unsigned int );
    /*! this container is added for 'node's only and stores all references to this node */
    QList<AbstractTreeItem*> m_reverseChildItems;
  protected:
    /*! internal use only: inserts a reversepath */
    void appendChildReversePath( AbstractTreeItem *item );
    /*! internal use only: inserts a forwardpath */
    void appendChildForwardPath( AbstractTreeItem *item );
    /*! internal use only: removes a reversepath */
    void removeChildReversePath( AbstractTreeItem *item );
};


#endif
