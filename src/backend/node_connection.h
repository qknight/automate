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
    /*! NULL or a valid AbstractTreeItem: can be set quit flexible */
    AbstractTreeItem* next_node();
    /*! dumps the internal data structure for debugging use */
    void dump();
    /*! sets the 'next node' to node*/
    void setNext_node( AbstractTreeItem* node );
    /*! returns the object type which is used in the model for example */
    unsigned int getObjectType();
    /*! we represent 'a' or 'b' (a label on a connection) internally as int, this int is stored here */
    unsigned int symbol_index();
    /*! reset the internal representation of a connection */
    void setSymbol_index( unsigned int symbol_index );
    /*! can't think of why this is used in a node_connection */
    void removeChild( unsigned int index );
    /*! this was added very late but showed to be helpful in many regards */
    node_connection* inverseConnection;
  private:
    /*! generates a unic id by calling it's parent recursively */
    unsigned int generateUniqueID( unsigned int );
    /*! internal symbol index variable, use setSymbol_index to set it*/
    unsigned int m_symbol_index;
    /*! internal storage of the next_node pointer */
    AbstractTreeItem* m_next_node;
};

#endif


