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

#ifndef ABSTRACTTREEITEM_H
#define ABSTRACTTREEITEM_H

#include <QVariant>
#include <QDebug>

#include "objectProperty.h"

/*! TreeItemType /struct */
enum TreeItemType {
  AUTOMATE_ROOT,
  NODE,
  NODE_CONNECTION,
  UNKNOWN
};

/*! AbstractTreeItem class is based on Qt4::SimpleTreeModel Example<br>
** The extended example is used as base class only.
** - Deriving classes overwrite specific functionality.
** - This class is extended by a custom object property system.
** - Every 'item' in the tree must have a uniq id
**  - There is only one AutomateRoot object with id=0 in each automate
**  - The AutomateRoot can assign ids to all other objects as node and node_connection
*/
class AbstractTreeItem : public objectProperty {
    friend class node;
    friend class node_connection;
    friend class AutomateRoot;
  public:
    /*! returns the number of childs:
      - 0 no childs
      - >0 child amount
      - <0 error
    */
    int childCount() const;
    /*! returns the m_childItems position offset of this in/from the parent item */
    int row() const;
    /*! returns the id for this item */
    unsigned int getId();
    /*! returns AbstractTreeItem* from the m_childItems list with index=row*/
    AbstractTreeItem *child( int row );
    /*! returns the parent item
      - only one item doesn't have a parent, that is the AutomateRoot
      - all other items MUST have a valid parent*/
    AbstractTreeItem *parent();
    /*! returns m_childItems.size() */
    QList<AbstractTreeItem*> childItems() const;
    /*! appends a new child to m_childItems, child has to have this as parent already! */
    virtual void appendChild( AbstractTreeItem *child );
    /*! returns the object type, see deriving classes for details */
    virtual unsigned int getObjectType() = 0;
    /*! removes a child from m_childItems */
    virtual void removeChild( unsigned int index ) = 0;
  protected:
    /*! WARNING: never delete objects as for instance childItems within the destructor
    since this will create inconsistencies between the model and this data structure.
    A better way is to fail with exit(0) since this problem must be handled with great care! */
    virtual ~AbstractTreeItem();

    /*! the constructor is protected to enforce the policy, which is:
      - only derived classes may be used to create objects from:
        - that is: AutomateRoot, node, node_connection*/
    AbstractTreeItem( AbstractTreeItem *parent = 0 );
    /*! this pure virtual function is used to compute a uniq ID. Only a AutomateRoot object can assign new IDs.
        the idea of using IDs is twofold: 
         - first: if someone uses scripts to modify an automate one can use the ideas instead of the pointers for identifying 
           objects
         - second: unlike the graphicsview (which is operated using the mouse with some keyboard shortcuts)
           the treeview relies to a naming sheme and it would be unwise to use the pointers which would somehow be converted to
           unsigned int values with a cast. 
        currently there is no other use of the ID system
    */
    virtual unsigned int generateUniqueID( unsigned int ) = 0;
    /*! id of this object
      - 0 is default but it's overwritten in the constructor of the deriving class
      - only the AutomateRoot may leave the 0 unchanged! */
    unsigned int ID;
    /*! see TreeItemType
      This variable is used to identify what kind of object we have.*/
    unsigned int objectType;
    /*! This container holds all child items */
    QList<AbstractTreeItem*> m_childItems;
    /*! This function was introduced when I found out that we need to move the reverse connection
        from one parent to another since we don't want to create a new reverse connection for every
        forward connection which changes it's destination.*/
    void setParent(AbstractTreeItem *parent);
    /*! This function dumps the whole data to stdout which is helpful when doing debugging. You could use the
        provided functionality also for other purposes as calling external algorithms which operate on the
        data structure of this automate. For example: automate_algorithms could be ported to this data structure
        so that one can convert a NDA to a DFA and stuff like that, see automate_algorithms.cpp */
    virtual void dump() = 0;
  private:
    /*! This parent item is used to traverse the tree upwards. */
    AbstractTreeItem *parentItem;
};

#endif
