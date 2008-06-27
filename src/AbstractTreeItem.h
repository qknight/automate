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

// based  on QT4::Simple Tree Model Example

#ifndef ABSTRACTTREEITEM_H
#define ABSTRACTTREEITEM_H

#include <QVariant>
#include <QDebug>

#include "objectProperty.h"

enum TreeItemType {
  AUTOMATE_ROOT,
  NODE,
  NODE_CONNECTION,
  UNKNOWN
};

class AbstractTreeItem : public objectProperty {
    friend class node;
    friend class node_connection;
    friend class AutomateRoot;

  protected:
    AbstractTreeItem( AbstractTreeItem *parent = 0 );
    virtual unsigned int generateUniqueID( unsigned int ) = 0;
    unsigned int ID;
    unsigned int objectType;
    QList<AbstractTreeItem*> m_childItems;
    void setParent(AbstractTreeItem *parent);
  public:
    virtual ~AbstractTreeItem();
    virtual void removeChild( unsigned int index ) = 0;
    virtual void appendChild( AbstractTreeItem *child );
    virtual void dump() = 0;
    virtual unsigned int getObjectType() = 0;
    AbstractTreeItem *child( int row );
    int childCount() const;
    int columnCount() const;
    QVariant data( int column ) const;
    int row() const;
    AbstractTreeItem *parent();
    unsigned int getId();
    QList<AbstractTreeItem*> childItems() const;
  private:
    AbstractTreeItem *parentItem;
    QList<QVariant> itemData;
};

#endif
