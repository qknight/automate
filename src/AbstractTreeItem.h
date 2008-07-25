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
**  - The AutomateRoot can assign ids to all other objects
*/
class AbstractTreeItem : public objectProperty {
    friend class node;
    friend class node_connection;
    friend class AutomateRoot;
  public:
    /*! destructor */
    virtual ~AbstractTreeItem();
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
    /*! the constructor is protected to enforce the policy, which is:
      - only derived classes may be used to create objects from:
        - that is: AutomateRoot, node, node_connection*/
    AbstractTreeItem( AbstractTreeItem *parent = 0 );
    /*! this pure virtual function is used to compute a uniq ID. Only a AutomateRoot object can do that */
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
